/* --COPYRIGHT--,EPL
 *  Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 * 
 * --/COPYRIGHT--*/
/*!
 *  @_nodoc
 *  ======== SymbolTable ========
 *  This module implements the ISymbolTable interface using DSS.
 *  This module is simply a wrapper for the xdc.rov.SymbolTable Java class.
 */
metaonly module SymbolTable inherits xdc.rov.ISymbolTable {

instance:
    
    /*!
     *  ======== create ========
     */
    create(Any session); 

}
