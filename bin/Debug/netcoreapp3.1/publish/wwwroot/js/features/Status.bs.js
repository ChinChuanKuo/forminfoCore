// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE


function statusModule(status) {
  switch (status) {
    case "deleteSuccess" :
        return "delete item successfully";
    case "errorFormLength" :
        return "the field column is to long";
    case "errorFormLogin" :
        return "if want used features, you need login";
    case "errorSearch" :
        return "sorry, you can not search information";
    case "islock" :
        return "can not use information";
    case "nodata" :
        return "undefined about database";
    case "saveSuccess" :
        return "this form save successfully";
    case "sendSuccess" :
        return "this form Send successfully";
    default:
      return status;
  }
}

function accountModule(account) {
  switch (account) {
    case "errorCode" :
        return "please enter your verification code";
    case "errorDifPassword" :
        return "please enter same password";
    case "errorEmail" :
        return "please enter your email";
    case "errorBirthday" :
    case "errorForget" :
        return "please enter your birthday";
    case "errorPassword" :
        return "please enter your password";
    case "errorResend" :
        return "please enter your first & Second password";
    case "errorUserid" :
        return "please enter your userid";
    case "errorUsername" :
        return "please enter your username";
    case "islock" :
        return "can not use information";
    case "nodata" :
        return "undefined about database";
    case "resend" :
        return "please find your mails";
    default:
      return account;
  }
}

function uploadModels(upload) {
  switch (upload) {
    case "failed" :
        return "sorry, this file uplaod failed";
    case "success" :
        return "congratulations, this file upload successfully";
    default:
      return upload;
  }
}

function downloadModels(download) {
  switch (download) {
    case "nodata" :
        return "sorry, this file undefined";
    case "success" :
        return "congratulations, this file download successfully";
    default:
      return download;
  }
}

function permissModels(permissajax) {
  switch (permissajax) {
    case "errorDelete" :
        return "sorry, you can not delete information";
    case "errorExport" :
        return "sorry, you can not export information";
    case "errorInsert" :
        return "sorry, you can not insert information";
    case "errorUpdate" :
        return "sorry, you can not update information";
    default:
      return permissajax;
  }
}

export {
  statusModule ,
  accountModule ,
  uploadModels ,
  downloadModels ,
  permissModels ,
  
}
/* No side effect */
