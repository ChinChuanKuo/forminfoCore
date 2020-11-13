// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as React from "react";

function widths(width) {
  if (width !== undefined) {
    return width;
  } else {
    return "100%";
  }
}

function heights(height) {
  if (height !== undefined) {
    return height;
  } else {
    return "auto";
  }
}

function borderRadiuses(borderRadius) {
  if (borderRadius !== undefined) {
    if (borderRadius === "circle") {
      return "50%";
    } else {
      return borderRadius + "px";
    }
  } else {
    return "0px";
  }
}

function $$Image(Props) {
  var width = Props.width;
  var height = Props.height;
  var borderRadius = Props.borderRadius;
  var src = Props.src;
  return React.createElement("img", {
              style: {
                cursor: "pointer",
                height: height !== undefined ? height : "auto",
                width: width !== undefined ? width : "100%",
                borderRadius: borderRadiuses(borderRadius)
              },
              src: src
            });
}

var make = $$Image;

export {
  widths ,
  heights ,
  borderRadiuses ,
  make ,
  
}
/* react Not a pure module */
