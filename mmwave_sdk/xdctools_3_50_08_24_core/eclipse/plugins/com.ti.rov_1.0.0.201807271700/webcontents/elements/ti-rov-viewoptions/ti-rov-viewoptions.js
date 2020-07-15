Polymer({ is : "ti-rov-viewoptions",

    behaviors: [rovBehaviors.viewBehaviors],

    properties: {
        viewArgsCallback : {
          type: Object,
          value: null
        },
        viewArgs : {
          type: Object,
          value: null
        },
        dlgArgs : { /* copy to append html'ish bindings to */
          type: Array,
          value: null
        },
        viewElem : {
          type: Object,
          value: null
        }
    },
    defaultViewOptionsMenuDialog : function (elem) {
        this.viewElem = elem;
        return (this.$.defaultViewOptionsMenuDialog);
    },
    defaultViewOptionsMenuItemSelected : function (e) {
        var selected = e.currentTarget.selectedItem.id;
        this.$.defaultViewOptionsMenu.selected = -1;
        if (selected != 'dividerItem') {
            this.$.defaultViewOptionsMenuDialog.close();
            this.viewElem[selected](e); /* id of the item is the function name */
        }
    },
    dividerChanged : function (e) {
        this.viewElem.dividerChanged(e);
    },
    dividerToggleClicked : function (e) {
        this.viewElem.dividerToggleClicked(e);
        this.$.dividerInput.disabled = !this.viewElem.repeatRefreshEnabled;
        this.$.dividerDisableIcon.hidden = !this.viewElem.repeatRefreshEnabled; 
        this.$.dividerEnableIcon.hidden = this.viewElem.repeatRefreshEnabled;
    },
    hasEmptyFields : function () {
        var foundEmpty = false;
        for(var i = 0; i < this.viewArgs.args.length; i++) {
            if ((this.viewArgs.args[i].type == 'string' || this.viewArgs.args[i].type == 'number') &&
                 this.$$('#arg_' + i).value == '') {
                foundEmpty = true;
                break;
            }
        }
        return (foundEmpty);
    },
    viewArgsCancelClicked : function (e) {
        if (this.viewArgsCallback) {
            var dialog = this.viewArgsCallback.elem.$.rovViewOptions.$.viewArgsDialog;
            if (dialog) {
                this.viewArgsCallback.elem[this.viewArgsCallback.fxn]('cancelled');
                this.viewArgsCallback = null;
                dialog.close();
            }
        }
    },
    viewArgsDialog : function (event, viewArgs, callbackObj) {
        var dialog = callbackObj.elem.$.rovViewOptions.$.viewArgsDialog;
        if (dialog) {
            dialog.resetFit();
            /* init the dialog bindings and calculate height */
            var height = 93;
            var foundEmpty = false;
            this.viewArgs = rovUtils.deepCopy(viewArgs);
            this.dlgArgs = rovUtils.deepCopy(viewArgs.args);
            for(var i = 0; i < this.dlgArgs.length; i++) {
                this.dlgArgs[i].id = 'arg_' + i;
                if (this.dlgArgs[i].type == 'string') {
                    this.dlgArgs[i].isString = true;
                    if (this.dlgArgs[i].value == '') {
                        foundEmpty = true;
                    }
                    height += 60;
                }
                else if (this.dlgArgs[i].type == 'number') {
                    this.dlgArgs[i].isNumber = true;
                    if (this.dlgArgs[i].value == '') {
                        foundEmpty = true;
                    }
                    height += 60;
                }
                else if (this.dlgArgs[i].type == 'boolean') {
                    this.dlgArgs[i].isBool = true;
                    this.dlgArgs[i].value = String(this.dlgArgs[i].value) == 'true';
                    height += 21;
                }
            }
            var left = event.x;
            if (event.currentTarget) {
                left -= 34;
            }
            var width = 235; /* ballpark from styling in html */
            if ((left + width) > document.documentElement.clientWidth) {
                left -= width;
            }
            dialog.style.left = left + 'px';
            dialog.style.height = height + 'px';
            dialog.style.maxHeight = height + 'px';
            var top = event.y;
            if (top + height > document.querySelector('ti-rov-panel').viewContainer.clientHeight) {
              top = top - height;
              if (top < 0) {
                  top = 0;
              }
            }
            dialog.style.top = top + 'px';
            dialog.open();
            dialog.style.zIndex = String(document.querySelector('ti-rov-panel').getMaxZindex() + 1);
            this.viewArgsCallback = callbackObj;
            this.$.viewArgsDialogOk.disabled = foundEmpty;
            this.$.dlgArgsTemplate.render()
        }
    },
    viewArgsKeyPress : function (e) {
        var keyCode = e.keyCode || e.which;
        if (keyCode === 13 && !this.hasEmptyFields()) {
            this.viewArgsOkClicked(e);
        }
    },
    viewArgsDialogOpened : function (e) {
        /* focus on and select all in the first input elem */
        for(var i = 0; i < this.dlgArgs.length; i++) {
            if (this.dlgArgs[i].isString || this.dlgArgs[i].isNumber) {
                var argElem = this.$$('#' + this.dlgArgs[i].id);
                argElem.$.input.focus();
                break;
            }
        }
    },
    viewArgsInputOnFocus : function (e) {
        e.currentTarget.$.input.select();
    },
    viewArgsOkClicked : function (e) {
        if (this.viewArgsCallback) {
            var dialog = this.viewArgsCallback.elem.$.rovViewOptions.$.viewArgsDialog;
            if (dialog) {
                for(var i = 0; i < this.viewArgs.args.length; i++) {
                    if (this.viewArgs.args[i].type == 'string' || this.viewArgs.args[i].type == 'number') {
                        this.viewArgs.args[i].value = this.$$('#arg_' + i).value
                    }
                    else if (this.viewArgs.args[i].type == 'boolean') {
                        this.viewArgs.args[i].value = this.$$('#arg_' + i).checked;
                    }
                }
                this.viewArgsCallback.elem[this.viewArgsCallback.fxn](null, this.viewArgs);
                this.viewArgsCallback = null;
                dialog.close();
            }
        }
    },
    viewArgsOnInput : function () {
        this.$.viewArgsDialogOk.disabled = this.hasEmptyFields();
    }
});

