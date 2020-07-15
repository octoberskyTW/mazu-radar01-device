/*
 *  ======== ProgressCallBack ========
 */
metaonly module ProgressCallBack inherits xdc.rov.ICallBack {

instance:

    create();

    /*!
     *  ======== args ========
     *  Optional arguments to the callback
     */
    config Any args;
}
