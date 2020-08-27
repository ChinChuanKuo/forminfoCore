type chartitem = {
  tile: string,
  color: string,
  to_: float,
}; //chart item information

type bottomitem = {
  actionShow: bool,
  icon: string,
  tile: string,
}; //bottom item information

type youtableitem = {
  tooltip: string,
  icon: string,
  value: string,
};

type optionitem = {
  optionPadding: bool,
  value: string,
};

type opticonitem = {
  opticonPadding: bool,
  icon: string,
  value: string,
};

type radioitem = {
  id: int,
  value: string,
};

type tabitem = {
  tabShow: bool,
  tabImage: string,
};

type tabtitem = {
  tabtShow: bool,
  tabImage: string,
  tabPath: string,
};