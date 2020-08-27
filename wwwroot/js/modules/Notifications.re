[@bs.val] [@bs.scope "Notice"] external make: string = "permission";
[@bs.val] [@bs.scope "Notice"]
external request: unit => Js.Promise.t(string) = "requestPermission";
[@bs.new] external message: string => unit = "Notice";