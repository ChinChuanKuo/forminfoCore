open Axios;
module Form = {
  let checkNew = data => postData("/Form/checkNewData", data);
  let loginForm = data => postData("/Form/loginFormData", data);
  let badgeForm = data => postData("/Form/badgeFormData", data);
  let permiss = data => postData("/Form/permissData", data);
  let record = data => postData("/Form/recordData", data);
  let badge = data => postData("/Form/badgeData", data);
};

module Login = {
  let checkUser = data => postData("/Login/checkUserData", data);
  let loginUser = data => postData("/Login/loginUserData", data);
};

module Forget = {
  let forgetUser = data => postData("/Forget/forgetUserData", data);
};

module Code = {
  let codeUser = data => postData("/Code/codeUserData", data);
};

module Resend = {
  let resendUser = data => postData("/Resend/resendUserData", data);
};

module Signup = {
  let signupUser = data => postData("/Signup/signupUserData", data);
};

module Icon = {
  let search = data => postData("/Icon/searchData", data);
  let insert = data => postData("/Icon/insertData", data);
};

module Option = {
  let add = data => postData("/Option/addData", data);
};

module Files = {
  let upload = formData =>
    postDatac(
      "/Files/uploadData",
      formData,
      makeConfig(
        ~headers=Headers.fromObj({"Content-Type": "multipart/form-data"}),
        (),
      ),
    );
  let website = data => postData("/Files/websiteData", data);
  let download = data => postData("/Files/downloadData", data);
};

module Default = {};

module Formor = {
  let search = data => postData("/Formor/searchData", data);
  let sType = data => postData("/Formor/sTypeData", data);
  let sVeri = data => postData("/Formor/sVeriData", data);
  let add = data => postData("/Formor/addData", data);
  let delete = data => postData("/Formor/deleteData", data);
  let insert = data => postData("/Formor/insertData", data);
};

module Proform = {
  let polling = data =>
    postDatac("/Proform/pollingData", data, makeConfig(~timeout=30000, ()));
  //let polling = data => postData("/Home/pollingData", data);
  let search = data => postData("/Proform/searchData", data);
};
