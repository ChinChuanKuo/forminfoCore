// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE


function userData(userid) {
  return {
          userid: userid
        };
}

function loginData(userid, password, longitude, latitude) {
  return {
          userid: userid,
          password: password,
          longitude: longitude,
          latitude: latitude
        };
}

function otherData(userid, values) {
  return {
          userid: userid,
          values: values
        };
}

function signupData(userid, password, username, birthday) {
  return {
          userid: userid,
          password: password,
          username: username,
          birthday: birthday
        };
}

function iIconData(items, qaitems, newid) {
  return {
          items: items,
          qaitems: qaitems,
          newid: newid
        };
}

function iSecuData(externip, newid) {
  return {
          externip: externip,
          newid: newid
        };
}

function iNotiData(isbool, newid) {
  return {
          isbool: isbool,
          newid: newid
        };
}

function sRowsData(formId, value, newid) {
  return {
          formId: formId,
          value: value,
          newid: newid
        };
}

function dFormData(formId, newid) {
  return {
          formId: formId,
          newid: newid
        };
}

function iItemsData(items, newid) {
  return {
          items: items,
          newid: newid
        };
}

function iFileData(formId, original, encryption, extension, newid) {
  return {
          formId: formId,
          original: original,
          encryption: encryption,
          extension: extension,
          newid: newid
        };
}

function iPathData(formId, imagePath, original, encryption, extension, newid) {
  return {
          formId: formId,
          imagePath: imagePath,
          original: original,
          encryption: encryption,
          extension: extension,
          newid: newid
        };
}

function iFormData(formId, items, newid) {
  return {
          formId: formId,
          items: items,
          newid: newid
        };
}

function iFormsData(tile, desc, items, settitems, dertitems, newid) {
  return {
          tile: tile,
          desc: desc,
          items: items,
          settitems: settitems,
          dertitems: dertitems,
          newid: newid
        };
}

function uFormsData(formId, tile, desc, items, settitems, newid) {
  return {
          formId: formId,
          tile: tile,
          desc: desc,
          items: items,
          settitems: settitems,
          newid: newid
        };
}

export {
  userData ,
  loginData ,
  otherData ,
  signupData ,
  iIconData ,
  iSecuData ,
  iNotiData ,
  sRowsData ,
  dFormData ,
  iItemsData ,
  iFileData ,
  iPathData ,
  iFormData ,
  iFormsData ,
  uFormsData ,
  
}
/* No side effect */
