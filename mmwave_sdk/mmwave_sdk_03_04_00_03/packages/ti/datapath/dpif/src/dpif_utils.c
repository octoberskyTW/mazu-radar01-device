/**
 *   @file  dpif_utils.c
 *
 *   @brief
 *      Implements utility functions for DPIF interface.
 *
 *  \par
 *  NOTE:
 *      (C) Copyright 2019 Texas Instruments, Inc.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**************************************************************************
 *************************** Include Files ********************************
 **************************************************************************/


/* Standard Include Files. */
#include <stdint.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include <ti/datapath/dpif/dpif_pointcloud.h>

#ifdef SUBSYS_DSS

/* C674x mathlib */
/* Suppress the mathlib.h warnings
 *  #48-D: incompatible redefinition of macro "TRUE"
 *  #48-D: incompatible redefinition of macro "FALSE"
 */
#pragma diag_push
#pragma diag_suppress 48
#include <ti/mathlib/mathlib.h>
#pragma diag_pop
#endif


/**
 *  @b Description
 *  @n
 *      Utility function to convert Cartesian point cloud to Spherical.
 *
 *  @pre    None
 *
 *  @param[in]  pointCloudCartesianIn   Input point cloud in cartesian format 
 *  @param[out] pointCloudSphericalOut  Output point cloud in spherical format  
 *  @param[in]  numPoints               Number of input points
 *
 *
 *  @retval
 *      Success     - 0
 *  @retval
 *      Error       - <0
 */
int32_t DPIFUtils_convertPointCloudCartesionToSpherical
(
    DPIF_PointCloudCartesian    *pointCloudCartesianIn,
    DPIF_PointCloudSpherical    *pointCloudSphericalOut,
    uint16_t                    numPoints
)
{
    int32_t retVal = 0;
    float   x, y, z;
    float   phi, theta;
    float   temp, range;
    int16_t count;

    /* Basic error Checking */
    if((pointCloudCartesianIn == NULL) || (pointCloudSphericalOut == NULL)) 
    {
        retVal = -1;
        goto exit;
    }

    if(numPoints == 0)
    {
        goto exit;
    }

    for(count = 0; count < numPoints; count++)
    {
        /* Just for better readibility */
        x = pointCloudCartesianIn[count].x;
        y = pointCloudCartesianIn[count].y;
        z = pointCloudCartesianIn[count].z;
        
        temp = (y*y) + (x*x) + (z*z);        
        if(temp > 0)
        {            
            /* Calculate range */
#ifdef SUBSYS_DSS            
            range = sqrtsp(temp);
#else
            range = sqrt(temp);
#endif                        
            /* Calculate elevation angle */
            phi = asin(z/range);
            /* Calculate azimuth angle */
            theta = asin(x/(range * cos(phi)));
        }
        else
        {   
            /* set everything to 0 */
            range = 0;            
            phi = 0;
            theta = 0;            
        }
        
        /* Assign the values to output structure */
        pointCloudSphericalOut[count].range = range;
        pointCloudSphericalOut[count].azimuthAngle = theta;
        pointCloudSphericalOut[count].elevAngle = phi;
        pointCloudSphericalOut[count].velocity = pointCloudCartesianIn[count].velocity;
    }
    
exit:
    return retVal;

}
