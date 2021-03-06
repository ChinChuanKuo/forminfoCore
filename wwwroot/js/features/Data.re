[@genType]
let userData = userid => {"userid": userid};
[@genType]
let loginData = (userid, password, longitude, latitude) => {
  "userid": userid,
  "password": password,
  "longitude": longitude,
  "latitude": latitude,
};
[@genType]
let otherData = (userid, values) => {"userid": userid, "values": values};
[@genType]
let signupData = (userid, password, username, birthday) => {
  "userid": userid,
  "password": password,
  "username": username,
  "birthday": birthday,
};
[@genType]
let iIconData = (items, qaitems, newid) => {
  "items": items,
  "qaitems": qaitems,
  "newid": newid,
};
[@genType]
let iSecuData = (externip, newid) => {"externip": externip, "newid": newid};
[@genType]
let iNotiData = (isbool, newid) => {"isbool": isbool, "newid": newid};
[@genType]
let sRowsData = (formId, value, newid) => {
  "formId": formId,
  "value": value,
  "newid": newid,
};
[@genType]
let dFormData = (formId, newid) => {"formId": formId, "newid": newid};
[@genType]
let iItemsData = (items, newid) => {"items": items, "newid": newid};
[@genType]
let iFileData = (formId, original, encryption, extension, newid) => {
  "formId": formId,
  "original": original,
  "encryption": encryption,
  "extension": extension,
  "newid": newid,
};
[@genType]
let iPathData = (formId, imagePath, original, encryption, extension, newid) => {
  "formId": formId,
  "imagePath": imagePath,
  "original": original,
  "encryption": encryption,
  "extension": extension,
  "newid": newid,
};
[@genType]
let iFormData = (formId, items, newid) => {
  "formId": formId,
  "items": items,
  "newid": newid,
};
[@genType]
let sFileData = (imagePath, original, encryption, extension, newid) => {
  "imagePath": imagePath,
  "original": original,
  "encryption": encryption,
  "extension": extension,
  "newid": newid,
};

[@genType]
let iFormsData = (tile, desc, items, settitems, dertitems, newid) => {
  "tile": tile,
  "desc": desc,
  "items": items,
  "settitems": settitems,
  "dertitems": dertitems,
  "newid": newid,
};
[@genType]
let uFormsData = (formId, tile, desc, items, settitems, dertitems, newid) => {
  "formId": formId,
  "tile": tile,
  "desc": desc,
  "items": items,
  "settitems": settitems,
  "dertitems": dertitems,
  "newid": newid,
};
