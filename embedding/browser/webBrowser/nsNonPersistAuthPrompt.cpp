/* -*- Mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */
/* ***** BEGIN LICENSE BLOCK *****
 * Version: NPL 1.1/GPL 2.0/LGPL 2.1
 *
 * The contents of this file are subject to the Netscape Public License
 * Version 1.1 (the "License"); you may not use this file except in
 * compliance with the License. You may obtain a copy of the License at
 * http://www.mozilla.org/NPL/
 *
 * Software distributed under the License is distributed on an "AS IS" basis,
 * WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
 * for the specific language governing rights and limitations under the
 * License.
 *
 * The Original Code is mozilla.org code.
 *
 * The Initial Developer of the Original Code is 
 * Netscape Communications Corporation.
 * Portions created by the Initial Developer are Copyright (C) 2001
 * the Initial Developer. All Rights Reserved.
 *
 * Contributor(s):
 *
 *
 * Alternatively, the contents of this file may be used under the terms of
 * either the GNU General Public License Version 2 or later (the "GPL"), or
 * the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
 * in which case the provisions of the GPL or the LGPL are applicable instead
 * of those above. If you wish to allow use of your version of this file only
 * under the terms of either the GPL or the LGPL, and not to allow others to
 * use your version of this file under the terms of the NPL, indicate your
 * decision by deleting the provisions above and replace them with the notice
 * and other provisions required by the GPL or the LGPL. If you do not delete
 * the provisions above, a recipient may use your version of this file under
 * the terms of any one of the NPL, the GPL or the LGPL.
 *
 * ***** END LICENSE BLOCK ***** */

#include "nsNonPersistAuthPrompt.h"

#include "nsReadableUtils.h"

//*****************************************************************************
// nsNonPersistAuthPrompt
//*****************************************************************************   

nsNonPersistAuthPrompt::nsNonPersistAuthPrompt()
{
    NS_INIT_REFCNT();
}

nsNonPersistAuthPrompt::~nsNonPersistAuthPrompt()
{
}

NS_IMPL_ISUPPORTS2(nsNonPersistAuthPrompt, nsISingleSignOnPrompt, nsIAuthPrompt)

//*****************************************************************************
// nsNonPersistAuthPrompt::nsISingleSignOnPrompt
//*****************************************************************************   

NS_IMETHODIMP nsNonPersistAuthPrompt::SetPromptDialogs(nsIPrompt *dialogs)
{
    mPromptDialogs = dialogs;
    return NS_OK;
}


//*****************************************************************************
// nsNonPersistAuthPrompt::nsIAuthPrompt
//*****************************************************************************   

NS_IMETHODIMP nsNonPersistAuthPrompt::Prompt(const PRUnichar *dialogTitle,
                                             const PRUnichar *text,
                                             const PRUnichar *passwordRealm,
                                             PRUint32 savePassword,
                                             const PRUnichar *defaultText,
                                             PRUnichar **result,
                                             PRBool *_retval)
{
    NS_ENSURE_TRUE(mPromptDialogs, NS_ERROR_NOT_INITIALIZED);
    NS_ENSURE_ARG_POINTER(result);
    
    *result = ToNewUnicode(nsDependentString(defaultText));
    if (*result == nsnull) return NS_ERROR_OUT_OF_MEMORY;
    return mPromptDialogs->Prompt(dialogTitle, text, result, nsnull, nsnull, _retval);
}

NS_IMETHODIMP nsNonPersistAuthPrompt::PromptUsernameAndPassword(const PRUnichar *dialogTitle,
                                                                const PRUnichar *text,
                                                                const PRUnichar *passwordRealm,
                                                                PRUint32 savePassword,
                                                                PRUnichar **user,
                                                                PRUnichar **pwd,
                                                                PRBool *_retval)
{
    NS_ENSURE_TRUE(mPromptDialogs, NS_ERROR_NOT_INITIALIZED);

    return mPromptDialogs->PromptUsernameAndPassword(dialogTitle, text, user, pwd, nsnull, nsnull, _retval);
}

NS_IMETHODIMP nsNonPersistAuthPrompt::PromptPassword(const PRUnichar *dialogTitle,
                                                     const PRUnichar *text,
                                                     const PRUnichar *passwordRealm,
                                                     PRUint32 savePassword,
                                                     PRUnichar **pwd,
                                                     PRBool *_retval)
{
    NS_ENSURE_TRUE(mPromptDialogs, NS_ERROR_NOT_INITIALIZED);

    return mPromptDialogs->PromptPassword(dialogTitle, text, pwd, nsnull, nsnull, _retval);
}
