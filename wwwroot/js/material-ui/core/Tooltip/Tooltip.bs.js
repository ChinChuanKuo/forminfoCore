// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Setting$BtsCore from "../../../setting/Setting.bs.js";

((require('../../scss/Tooltip/tooltip.scss')));

function reducer(param, action) {
  return {
          enter: action[0]
        };
}

var initialState = {
  enter: false
};

function widths(width) {
  if (width !== undefined) {
    return width;
  } else {
    return "max-content";
  }
}

function tops($$location) {
  switch ($$location) {
    case "left" :
    case "right" :
        return "50%";
    case "top" :
    case "topLeft" :
    case "topRight" :
        return "0";
    default:
      return "auto";
  }
}

function rights($$location) {
  switch ($$location) {
    case "bottomRight" :
    case "right" :
    case "topRight" :
        return "0";
    default:
      return "auto";
  }
}

function bottoms($$location) {
  switch ($$location) {
    case "bottom" :
    case "bottomLeft" :
    case "bottomRight" :
        return "0";
    default:
      return "auto";
  }
}

function lefts($$location) {
  switch ($$location) {
    case "top" :
        return "50%";
    case "bottomLeft" :
    case "left" :
    case "topLeft" :
        return "0";
    default:
      return "auto";
  }
}

function transforms($$location) {
  switch ($$location) {
    case "bottom" :
        return "translate(-50%, 150%)";
    case "bottomLeft" :
        return "translate(-100%, 150%)";
    case "bottomRight" :
        return "translate(100%, 150%)";
    case "left" :
        return "translate(-100%, -50%)";
    case "right" :
        return "translate(100%, -50%)";
    case "topLeft" :
        return "translate(-100%, -150%)";
    case "topRight" :
        return "translate(100%, -150%)";
    default:
      return "translate(-50%, -150%)";
  }
}

function backgroundColors(backgroundColor) {
  if (backgroundColor !== undefined) {
    return backgroundColor;
  } else {
    return "rgba(0,0,0,1)";
  }
}

function colors(color) {
  if (color !== undefined) {
    return color;
  } else {
    return "rgba(255,255,255,1)";
  }
}

function fontSizes(fontSize) {
  if (fontSize !== undefined) {
    return fontSize + "px";
  } else {
    return "12px";
  }
}

function Tooltip(Props) {
  var style = Props.style;
  var width = Props.width;
  var $$location = Props.location;
  var backgroundColor = Props.backgroundColor;
  var color = Props.color;
  var fontSize = Props.fontSize;
  var children = Props.children;
  var match = React.useReducer(reducer, initialState);
  var dispatch = match[1];
  return React.createElement("div", {
              className: "tooltip",
              onMouseEnter: (function (param) {
                  return Curry._1(dispatch, /* MouseEnterLeave */[true]);
                }),
              onMouseLeave: (function (param) {
                  return Curry._1(dispatch, /* MouseEnterLeave */[false]);
                })
            }, React.createElement("span", {
                  className: "tooltiptext",
                  style: Object.assign(({}), {
                        backgroundColor: backgroundColor !== undefined ? backgroundColor : "rgba(0,0,0,1)",
                        bottom: bottoms(Setting$BtsCore.stringObjects($$location)),
                        color: color !== undefined ? color : "rgba(255,255,255,1)",
                        fontSize: fontSizes(fontSize),
                        left: lefts(Setting$BtsCore.stringObjects($$location)),
                        right: rights(Setting$BtsCore.stringObjects($$location)),
                        top: tops(Setting$BtsCore.stringObjects($$location)),
                        visibility: match[0].enter ? "visible" : "hidden",
                        width: width !== undefined ? width : "max-content",
                        transform: transforms(Setting$BtsCore.stringObjects($$location))
                      }, Setting$BtsCore.styleObjects(style))
                }, children));
}

var make = Tooltip;

export {
  reducer ,
  initialState ,
  widths ,
  tops ,
  rights ,
  bottoms ,
  lefts ,
  transforms ,
  backgroundColors ,
  colors ,
  fontSizes ,
  make ,
  
}
/*  Not a pure module */
