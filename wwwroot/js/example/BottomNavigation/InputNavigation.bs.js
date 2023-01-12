// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as React from "react";
import * as Caml_option from "bs-platform/lib/es6/caml_option.js";
import * as Setting$BtsCore from "../../setting/Setting.bs.js";
import * as ToolBar$BtsCore from "../ToolBar/ToolBar.bs.js";
import * as GridItem$BtsCore from "../../material-ui/core/Grid/GridItem.bs.js";
import * as GridContainer$BtsCore from "../../material-ui/core/Grid/GridContainer.bs.js";
import * as TextFieldArticle$BtsCore from "../../material-ui/core/TextField/TextFieldArticle.bs.js";

function InputNavigation(Props) {
  var textRef = Props.textRef;
  var disabled = Props.disabled;
  var onInput = Props.onInput;
  var onKeyDown = Props.onKeyDown;
  var children = Props.children;
  var tmp = {
    maxHeight: "121",
    height: "80",
    textRef: Setting$BtsCore.refObjects(textRef),
    disabled: Setting$BtsCore.disabledObjects(disabled)
  };
  if (onInput !== undefined) {
    tmp.onInput = Caml_option.valFromOption(onInput);
  }
  if (onKeyDown !== undefined) {
    tmp.onKeyDown = Caml_option.valFromOption(onKeyDown);
  }
  return React.createElement(GridContainer$BtsCore.make, {
              direction: "column",
              justify: "center",
              alignItem: "stretch",
              children: null
            }, React.createElement(GridItem$BtsCore.make, {
                  top: "0",
                  bottom: "6",
                  xs: "auto",
                  children: React.createElement(ToolBar$BtsCore.make, {
                        disabled: Setting$BtsCore.disabledObjects(disabled)
                      })
                }), React.createElement(GridItem$BtsCore.make, {
                  top: "0",
                  bottom: "0",
                  xs: "auto",
                  children: React.createElement(TextFieldArticle$BtsCore.make, tmp)
                }), React.createElement(GridItem$BtsCore.make, {
                  top: "6",
                  bottom: "0",
                  xs: "auto",
                  children: children
                }));
}

var make = InputNavigation;

export {
  make ,
  
}
/* react Not a pure module */
