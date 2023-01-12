// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE

import * as Curry from "bs-platform/lib/es6/curry.js";
import * as React from "react";
import * as Setting$BtsCore from "../../../setting/Setting.bs.js";

function reducer(param, action) {
  return {
          enter: action[0]
        };
}

var initialState = {
  enter: false
};

function paddings(padding) {
  if (padding !== undefined) {
    return padding + "px";
  } else {
    return "12px";
  }
}

function widths(width) {
  if (width !== undefined) {
    return width;
  } else {
    return "auto";
  }
}

function cursors(cursor) {
  if (cursor !== undefined) {
    return cursor;
  } else {
    return "inherit";
  }
}

function borderWidths(borderWidth) {
  if (borderWidth !== undefined) {
    return borderWidth + "px";
  } else {
    return "1px";
  }
}

function borderStyles(borderStyle) {
  if (borderStyle !== undefined) {
    return borderStyle;
  } else {
    return "solid";
  }
}

function borderColors(borderColor) {
  if (borderColor !== undefined) {
    return borderColor;
  } else {
    return "transparent";
  }
}

function borderRadiuses(borderRadius) {
  if (borderRadius !== undefined) {
    return borderRadius + "px";
  } else {
    return "0px";
  }
}

function enterBackgroundColors(enterBackgroundColor) {
  if (enterBackgroundColor !== undefined) {
    return enterBackgroundColor;
  } else {
    return "rgba(255,255,255,1)";
  }
}

function backgroundColors(backgroundColor) {
  if (backgroundColor !== undefined) {
    return backgroundColor;
  } else {
    return "rgba(255,255,255,1)";
  }
}

function flexGrows(xs, flexGrow) {
  switch (xs) {
    case "auto" :
        if (flexGrow !== undefined) {
          if (flexGrow !== undefined) {
            return flexGrow;
          } else {
            return "0";
          }
        } else {
          return "1";
        }
    case "no" :
        if (flexGrow !== undefined) {
          if (flexGrow !== undefined) {
            return flexGrow;
          } else {
            return "0";
          }
        } else {
          return "";
        }
    default:
      if (flexGrow !== undefined) {
        return flexGrow;
      } else {
        return "0";
      }
  }
}

function maxWidths(xs, maxWidth) {
  switch (xs) {
    case "1" :
        if (maxWidth !== undefined) {
          if (maxWidth !== undefined) {
            return maxWidth;
          } else {
            return "100%";
          }
        } else {
          return "8.34%";
        }
    case "10" :
        if (maxWidth !== undefined) {
          if (maxWidth !== undefined) {
            return maxWidth;
          } else {
            return "100%";
          }
        } else {
          return "83.34%";
        }
    case "11" :
        if (maxWidth !== undefined) {
          if (maxWidth !== undefined) {
            return maxWidth;
          } else {
            return "100%";
          }
        } else {
          return "91.67%";
        }
    case "2" :
        if (maxWidth !== undefined) {
          if (maxWidth !== undefined) {
            return maxWidth;
          } else {
            return "100%";
          }
        } else {
          return "16.67%";
        }
    case "3" :
        if (maxWidth !== undefined) {
          if (maxWidth !== undefined) {
            return maxWidth;
          } else {
            return "100%";
          }
        } else {
          return "25%";
        }
    case "4" :
        if (maxWidth !== undefined) {
          if (maxWidth !== undefined) {
            return maxWidth;
          } else {
            return "100%";
          }
        } else {
          return "33.34%";
        }
    case "5" :
        if (maxWidth !== undefined) {
          if (maxWidth !== undefined) {
            return maxWidth;
          } else {
            return "100%";
          }
        } else {
          return "41.67%";
        }
    case "6" :
        if (maxWidth !== undefined) {
          if (maxWidth !== undefined) {
            return maxWidth;
          } else {
            return "100%";
          }
        } else {
          return "50%";
        }
    case "7" :
        if (maxWidth !== undefined) {
          if (maxWidth !== undefined) {
            return maxWidth;
          } else {
            return "100%";
          }
        } else {
          return "58.34%";
        }
    case "8" :
        if (maxWidth !== undefined) {
          if (maxWidth !== undefined) {
            return maxWidth;
          } else {
            return "100%";
          }
        } else {
          return "66.67%";
        }
    case "9" :
        if (maxWidth !== undefined) {
          if (maxWidth !== undefined) {
            return maxWidth;
          } else {
            return "100%";
          }
        } else {
          return "75%";
        }
    case "no" :
        if (maxWidth !== undefined) {
          if (maxWidth !== undefined) {
            return maxWidth;
          } else {
            return "100%";
          }
        } else {
          return "";
        }
    default:
      if (maxWidth !== undefined) {
        return maxWidth;
      } else {
        return "100%";
      }
  }
}

function flexBasises(xs, flexBasis) {
  switch (xs) {
    case "1" :
        if (flexBasis !== undefined) {
          if (flexBasis !== undefined) {
            return flexBasis;
          } else {
            return "0";
          }
        } else {
          return "8.34%";
        }
    case "10" :
        if (flexBasis !== undefined) {
          if (flexBasis !== undefined) {
            return flexBasis;
          } else {
            return "0";
          }
        } else {
          return "83.34%";
        }
    case "11" :
        if (flexBasis !== undefined) {
          if (flexBasis !== undefined) {
            return flexBasis;
          } else {
            return "0";
          }
        } else {
          return "91.67%";
        }
    case "12" :
        if (flexBasis !== undefined) {
          if (flexBasis !== undefined) {
            return flexBasis;
          } else {
            return "0";
          }
        } else {
          return "100%";
        }
    case "2" :
        if (flexBasis !== undefined) {
          if (flexBasis !== undefined) {
            return flexBasis;
          } else {
            return "0";
          }
        } else {
          return "16.67%";
        }
    case "3" :
        if (flexBasis !== undefined) {
          if (flexBasis !== undefined) {
            return flexBasis;
          } else {
            return "0";
          }
        } else {
          return "25%";
        }
    case "4" :
        if (flexBasis !== undefined) {
          if (flexBasis !== undefined) {
            return flexBasis;
          } else {
            return "0";
          }
        } else {
          return "33.34%";
        }
    case "5" :
        if (flexBasis !== undefined) {
          if (flexBasis !== undefined) {
            return flexBasis;
          } else {
            return "0";
          }
        } else {
          return "41.67%";
        }
    case "6" :
        if (flexBasis !== undefined) {
          if (flexBasis !== undefined) {
            return flexBasis;
          } else {
            return "0";
          }
        } else {
          return "50%";
        }
    case "7" :
        if (flexBasis !== undefined) {
          if (flexBasis !== undefined) {
            return flexBasis;
          } else {
            return "0";
          }
        } else {
          return "58.34%";
        }
    case "8" :
        if (flexBasis !== undefined) {
          if (flexBasis !== undefined) {
            return flexBasis;
          } else {
            return "0";
          }
        } else {
          return "66.67%";
        }
    case "9" :
        if (flexBasis !== undefined) {
          if (flexBasis !== undefined) {
            return flexBasis;
          } else {
            return "0";
          }
        } else {
          return "75%";
        }
    case "no" :
        if (flexBasis !== undefined) {
          if (flexBasis !== undefined) {
            return flexBasis;
          } else {
            return "0";
          }
        } else {
          return "";
        }
    default:
      if (flexBasis !== undefined) {
        return flexBasis;
      } else {
        return "0";
      }
  }
}

function GridItem(Props) {
  var style = Props.style;
  var top = Props.top;
  var right = Props.right;
  var bottom = Props.bottom;
  var left = Props.left;
  var width = Props.width;
  var cursor = Props.cursor;
  var enterBorderWidth = Props.enterBorderWidth;
  var borderWidth = Props.borderWidth;
  var enterBorderStyle = Props.enterBorderStyle;
  var borderStyle = Props.borderStyle;
  var enterBorderColor = Props.enterBorderColor;
  var borderColor = Props.borderColor;
  var enterBorderRadius = Props.enterBorderRadius;
  var borderRadius = Props.borderRadius;
  var enterBackgroundColor = Props.enterBackgroundColor;
  var backgroundColor = Props.backgroundColor;
  var xs = Props.xs;
  var flexGrow = Props.flexGrow;
  var maxWidth = Props.maxWidth;
  var flexBasis = Props.flexBasis;
  var className = Props.className;
  var children = Props.children;
  var match = React.useReducer(reducer, initialState);
  var dispatch = match[1];
  var state = match[0];
  return React.createElement("div", {
              className: Setting$BtsCore.stringObjects(className),
              style: Object.assign(({}), {
                    backgroundColor: state.enter ? (
                        enterBackgroundColor !== undefined ? enterBackgroundColor : "rgba(255,255,255,1)"
                      ) : (
                        backgroundColor !== undefined ? backgroundColor : "rgba(255,255,255,1)"
                      ),
                    borderColor: state.enter ? (
                        enterBorderColor !== undefined ? enterBorderColor : "transparent"
                      ) : (
                        borderColor !== undefined ? borderColor : "transparent"
                      ),
                    borderStyle: state.enter ? (
                        enterBorderStyle !== undefined ? enterBorderStyle : "solid"
                      ) : (
                        borderStyle !== undefined ? borderStyle : "solid"
                      ),
                    borderWidth: state.enter ? borderWidths(enterBorderWidth) : borderWidths(borderWidth),
                    cursor: cursor !== undefined ? cursor : "inherit",
                    maxWidth: maxWidths(Setting$BtsCore.stringObjects(xs), maxWidth),
                    paddingTop: paddings(top),
                    paddingRight: paddings(right),
                    paddingBottom: paddings(bottom),
                    paddingLeft: paddings(left),
                    width: width !== undefined ? width : "auto",
                    borderRadius: state.enter ? borderRadiuses(enterBorderRadius) : borderRadiuses(borderRadius),
                    flexBasis: flexBasises(Setting$BtsCore.stringObjects(xs), flexBasis),
                    flexGrow: flexGrows(Setting$BtsCore.stringObjects(xs), flexGrow)
                  }, Setting$BtsCore.styleObjects(style)),
              onMouseEnter: (function (param) {
                  return Curry._1(dispatch, /* MouseEnterLeave */[true]);
                }),
              onMouseLeave: (function (param) {
                  return Curry._1(dispatch, /* MouseEnterLeave */[false]);
                })
            }, children);
}

var make = GridItem;

export {
  reducer ,
  initialState ,
  paddings ,
  widths ,
  cursors ,
  borderWidths ,
  borderStyles ,
  borderColors ,
  borderRadiuses ,
  enterBackgroundColors ,
  backgroundColors ,
  flexGrows ,
  maxWidths ,
  flexBasises ,
  make ,
  
}
/* react Not a pure module */
