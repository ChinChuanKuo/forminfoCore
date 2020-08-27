module Browser = {
  [@bs.val] [@bs.scope "navigator"] external make: string = "userAgent";
};

module Position = {
  [@bs.val] [@bs.scope "navigator.geolocation"]
  external make:
    (Js.t('a) => unit, Js.t('a) => unit, array(Basic.Location.item)) =>
    unit =
    "getCurrentPosition";
};

module Language = {
  [@bs.val] [@bs.scope "navigator"] external make: string = "language";
};