/****************************************************************************/
/*  strftime                                                                */
/*                                                                          */
/* Copyright (c) 1993 Texas Instruments Incorporated                        */
/* http://www.ti.com/                                                       */
/*                                                                          */
/*  Redistribution and  use in source  and binary forms, with  or without   */
/*  modification,  are permitted provided  that the  following conditions   */
/*  are met:                                                                */
/*                                                                          */
/*     Redistributions  of source  code must  retain the  above copyright   */
/*     notice, this list of conditions and the following disclaimer.        */
/*                                                                          */
/*     Redistributions in binary form  must reproduce the above copyright   */
/*     notice, this  list of conditions  and the following  disclaimer in   */
/*     the  documentation  and/or   other  materials  provided  with  the   */
/*     distribution.                                                        */
/*                                                                          */
/*     Neither the  name of Texas Instruments Incorporated  nor the names   */
/*     of its  contributors may  be used to  endorse or  promote products   */
/*     derived  from   this  software  without   specific  prior  written   */
/*     permission.                                                          */
/*                                                                          */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS   */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT   */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT   */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT   */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    */
/*                                                                          */
/****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*--------------------------------------------------------------------------*/
/* UNDEF INLINE CONTROL MACRO TO DISABLE INLINE OF ANY STRING FUNCTION      */
/* FOR CODESIZE CONSIDERATION.                                              */
/*--------------------------------------------------------------------------*/
#undef _INLINE
#undef        _IDECL
#define       _IDECL
#include <string.h>

#define P(year) (((year) + (year)/4 - (year)/100 + (year)/400) % 7)
#define NUMWEEKS(year) (52 + (P(year) == 4 || P(year-1) == 3))

static const _DATA_ACCESS char *const fday[] =
           { "Sunday","Monday","Tuesday","Wednesday",
	     "Thursday","Friday","Saturday" };

static const _DATA_ACCESS char *const fmon[] =
	   { "January","February","March","April","May",
	     "June", "July","August","September",
	     "October","November", "December" };

_CODE_ACCESS size_t strftime(char            * __restrict out,
	                     size_t                       maxsize,
	                     const char      * __restrict format,
	                     const struct tm * __restrict time)
{
    int       count = 0;
    char      buf[37];
    size_t    bufsz = sizeof(buf);

    for (;;)
    {
	while ((count < maxsize) && *format && (*format != '%'))
	{
	    count++;
	    *out++ = *format++;
	}

	if (count >= maxsize) return 0;
	if (*format == '\0')  { *out = 0; return count; }

        /*-------------------------------------------------------------------*/
        /* In the "C" locale, the C99 E and O modifiers are ignored          */
        /*-------------------------------------------------------------------*/
        if (format[1] == 'E' || format[1] == 'O') format++;

        /*-------------------------------------------------------------------*/
        /* Some formats require the ISO 8601 week-based calendar, which is   */
        /* quite hairy.  Pre-compute these values.                           */
        /* If the day actually falls in the previous or next week-based      */
        /* calendar year, adjust both the year and week.                     */
        /*-------------------------------------------------------------------*/
        int iso8601_weekday = time->tm_wday ? time->tm_wday : 7;
        int weekbased_year = time->tm_year + 1900;
        int weekbased_week = (time->tm_yday + 1 - iso8601_weekday + 10) / 7;

        if (weekbased_week == 0)
        {
            weekbased_year--;
            weekbased_week = NUMWEEKS(weekbased_year);
        }
        else if (weekbased_week > NUMWEEKS(weekbased_year))
        {
            weekbased_year++;
            weekbased_week = 1;
        }

	switch (*++format)
	{
	    case 'a' : /* C89: locale's abbreviated weekday name */
            {
                snprintf(buf, bufsz, "%.3s", fday[time->tm_wday]);
                break;
            }
	    case 'A' : /* C89: locale's full weekday name */
            {
                snprintf(buf, bufsz, "%s", fday[time->tm_wday]);
                break;
            }
            case 'h' : /* C99: equivalent to %b */
            case 'b' : /* C89: locale's abbreviated month name */
            {
                snprintf(buf, bufsz, "%.3s", fmon[time->tm_mon]);
                break;
            }
	    case 'B' : /* C89: locale's full month name */
            {
                snprintf(buf, bufsz, "%s", fmon[time->tm_mon]);
                break;
            }
            case 'c' : /* C89: locale's date and time representation.
                          For "C" locale, "%a %b %e %T %Y" */
            {
                strftime(buf, bufsz, "%a %b %e %T %Y", time);
                break;
            }
	    case 'C' : /* C99: calendar century [00-99] */
            {
                snprintf(buf, bufsz, "%02d", time->tm_year / 100 + 19);
                break;
            }
            case 'd' : /* C89: day of the month [01-31] */
            {
                snprintf(buf, bufsz, "%02d", time->tm_mday);
                break;
            }
            case 'x' : /* C89: locale's date representation.
                          For "C" locale, "%m/%d/%y" */
	    case 'D' : /* C99: %m/%d/%y */
            {
                strftime(buf, bufsz, "%m/%d/%y", time);
                break;
            }
            case 'e' : /* C99: day of the month [ 1-31] */
            {
                snprintf(buf, bufsz, "%2d", time->tm_mday);
                break;
            }
	    case 'F' : /* C99: %Y-%m-%d (ISO 8601 date format) */
            {
                strftime(buf, bufsz, "%Y-%m-%d", time);
                break;
            }
            case 'g' : /* C99: week based calendar year (last 2 digits) */
            {
                snprintf(buf, bufsz, "%02d", weekbased_year % 100);
                break;
            }
            case 'G' : /* C99: week based calendar year */
            {
                snprintf(buf, bufsz, "%d", weekbased_year);
                break;
            }
            /* see above for case 'h' */
            case 'H' : /* C89: hour (24-hour) [00-23] */
            {
                snprintf(buf, bufsz, "%02d", time->tm_hour);
                break;
            }
            case 'I' : /* C89: hour (12-hour) [01-12] */
            {
                snprintf(buf, bufsz, "%02d",
                         ((time->tm_hour != 0) &&
                          (time->tm_hour != 12)) ?
                         time->tm_hour % 12 : 12);
                break;
            }
            case 'j' : /* C89: day of the year [001-366] */
            {
                snprintf(buf, bufsz, "%03d", time->tm_yday + 1);
                break;
            }
            case 'm' : /* C89: month [01-12] */
            {
                snprintf(buf, bufsz, "%02d", time->tm_mon + 1);
                break;
            }
            case 'M' : /* C89: minute [00-59] */
            {
                snprintf(buf, bufsz, "%02d", time->tm_min);
                break;
            }
            case 'n' : /* C99: newline character */
            {
                snprintf(buf, bufsz, "\n");
                break;
            }
            case 'p' : /* C89: locale's equivalent of AM/PM */
            {
                snprintf(buf, bufsz, "%s", time->tm_hour >= 12 ? "PM":"AM");
                break;
            }
            case 'r' : /* C99: the locale's 12-hour clock time.
                          For "C" locale, "%I:%M:%S %p" */
            {
                strftime(buf, bufsz, "%I:%M:%S %p", time);
                break;
            }
            case 'R' : /* C99: %H:%M */
            {
                strftime(buf, bufsz, "%H:%M", time);
                break;
            }
            case 'S' : /* C89: second [00-60] */
            {
                snprintf(buf, bufsz, "%02d", time->tm_sec);
                break;
            }
            case 't' : /* C99: tab character */
            {
                snprintf(buf, bufsz, "\t");
                break;
            }
            case 'X' : /* C89: locale's time representation.
                          For "C" locale, "%T" */
            case 'T' : /* C99: %H:%M:%S (ISO 8601 time format) */
            {
                strftime(buf, bufsz, "%H:%M:%S", time);
                break;
            }
            case 'u' : /* C99: ISO 8601 weekday [1-7, where Monday is 1] */
            {
                snprintf(buf, bufsz, "%d", iso8601_weekday);
                break;
            }
            case 'U' : /* C89: week of the year (1st Sunday is first day 
                          of week 1 [00-53] */
            {
                snprintf(buf, bufsz, "%02d", time->tm_yday / 7 +
                         (time->tm_yday % 7 >= time->tm_wday));
                break;

            }
            case 'V' : /* C99: week-based calendar week of the year */
            {
                snprintf(buf, bufsz, "%02d", weekbased_week);
                break;
            }
            case 'w' : /* C89: weekday [0-6, where Sunday is 0] */
            {
                snprintf(buf, bufsz, "%d", time->tm_wday);
                break;
            }
            case 'W' : /* C89: week of the year (1st Monday is first day
                          of week 1 [00-53] */
            {
                snprintf(buf, bufsz, "%02d", time->tm_yday / 7 +
                         (time->tm_yday % 7 >= (time->tm_wday + 6) % 7));
                break;
            }
            /* see above for case 'x' */
            /* see above for case 'X' */
            case 'y' : /* C89: last two digits of year [00-99] */
            {
                snprintf(buf, bufsz, "%02d", time->tm_year % 100);
                break;
            }
            case 'Y' : /* C89: year [1997] */
            {
                snprintf(buf, bufsz, "%d", time->tm_year + 1900);
                break;
            }
	    case 'z' : /* C99: ISO8601 offset from UTC [-0600]
                          (or blank if indet.) */
            {
                if (time->tm_isdst < 0)
                {
                    long offset = labs(_tz.timezone);
                    snprintf(buf, bufsz, "%c%02ld%02ld",
                             _tz.timezone < 0 ? '+' : '-',
                             offset / 60 / 60,
                             offset / 60 % 60);
                }
                else buf[0] = '\0';
                break;
            }
	    case 'Z' : /* C89: locale's time zone name or abbrev,
                          (or blank if indet.) */
            {
                if (time->tm_isdst < 0)
                    snprintf(buf, bufsz, "%s", _tz.tzname);
                else buf[0] = '\0';
                break;
            }
	    case '%' : /* C89: '%' character */
            {
                strcpy(buf, "%");
                break;
            }
	}

	/*-------------------------------------------------------------*/
	/* IF THIS STRING WILL FIT IN BUFFER, APPEND IT.               */
	/*-------------------------------------------------------------*/
	if ((count += strlen(buf)) > maxsize) return 0;
	strcpy(out, buf);
	out += strlen(buf);
	format++;
    }
}

