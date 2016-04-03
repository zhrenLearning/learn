//侧边栏菜单切换
var sideTabs=function(){
    function tag(name,elem){
        return (elem||document).getElementsByTagName(name);
    }
    //获得相应ID的元素
    function id(name){
        return document.getElementById(name);
    }
    function first(elem){
        elem=elem.firstChild;
        return elem&&elem.nodeType==1? elem:next(elem);
    }
    function next(elem){
        do{
            elem=elem.nextSibling;  
        }while(
            elem&&elem.nodeType!=1  
        )
        return elem;
    }
        return {
        set:function priceMenuShow(elemId,tabId){
            var elem=tag("li",id(elemId));
            var tabs=tag("ul",id(tabId));
            var listNum=elem.length;
            var tabNum=tabs.length;
            for(var i=0;i<listNum;i++){
                    elem[i].onclick=(function(i){
                        return function(){
                            for(var j=0;j<tabNum;j++){
                                if(i==j){
                                    tabs[j].style.display="block";
                                    //alert(elem[j].firstChild);
                                    elem[j].className="current";

                                }
                                else{
                                    tabs[j].style.display="none";
                                    elem[j].className="";
                                }
                            }
                        }
                    })(i)
            }
        }
    }
}();
sideTabs.set("sideMenu","tagNav");//执行

//横向菜单切换
var tabs=function(){
    function tag(name,elem){
        return (elem||document).getElementsByTagName(name);
    }
    //获得相应ID的元素
    function id(name){
        return document.getElementById(name);
    }
    function first(elem){
        elem=elem.firstChild;
        return elem&&elem.nodeType==1? elem:next(elem);
    }
    function next(elem){
        do{
            elem=elem.nextSibling;  
        }while(
            elem&&elem.nodeType!=1  
        )
        return elem;
    }
    return {
        set:function priceShow(elemId,tabId){
            var elem=tag("li",id(elemId));
            var tabs=tag("ul",id(tabId));
            var listNum=elem.length;
            var tabNum=tabs.length;
            for(var i=0;i<listNum;i++){
                    elem[i].onclick=(function(i){
                        return function(){
                            for(var j=0;j<tabNum;j++){
                                if(i==j){
                                    tabs[j].style.display="block";
                                    //alert(elem[j].firstChild);
                                    elem[j].firstChild.className="current";
                                    elem[j].style.backgroundImage="url(images/bg-checked.jpg)";
                                    elem[j].style.color="#fff";
                                    elem[j].childNodes[1].style.visibility="visible";
                                }
                                else{
                                    tabs[j].style.display="none";
                                    elem[j].firstChild.className="";
                                    elem[j].style.backgroundImage="url(images/bg-uncheck.jpg)";
                                    elem[j].style.color="#333";
                                    elem[j].childNodes[1].style.visibility="hidden";

                                }
                            }
                        }
                    })(i)
            }
        }
    }
}();
tabs.set("nav01","menu_con");//执行
tabs.set("nav02","menu_con");//执行
tabs.set("nav03","menu_con");//执行
tabs.set("nav04","menu_con");//执行
tabs.set("nav05","menu_con");//执行
tabs.set("nav06","menu_con");//执行
tabs.set("nav07","menu_con");//执行
tabs.set("nav08","menu_con");//执行

//机型故障选择
function set_problems(types, problems){
    phoneProArray = new Object(); 
    phoneProArray['iPhone5']=new Array('台北','台南','其他'); 
    phoneProArray['iPhone6']=new Array('Malaysia'); 
    phoneProArray['iPhone6s']=new Array('北京'); 
    var phoneType, phonePro; 
    var x, y; 
    phoneType=types.value; 
    phonePro=problems.value; 
    problems.length=1; 
    if(phoneType=='0') return; 
    if(typeof(phoneProArray[phoneType])=='undefined') return; 
    for(x=0; x<phoneProArray[phoneType].length; x++) { 
        y = x+1; 
        problems.options[y] = new Option(); 
        problems.options[y].text = phoneProArray[phoneType][x]; 
        problems.options[y].value = phoneProArray[phoneType][x];
    };
    document.getElementById("priceShow").innerHTML="000";
};
//地区选择
function set_city(city, areas){ 
    cities = new Object(); 
    cities['台湾']=new Array('台北','台南','其他'); 
    cities['马来西亚']=new Array('Malaysia'); 
    cities['北京']=new Array('北京'); 
    var cityValue, areaValue; 
    var i, ii; 
    cityValue=city.value; 
    areaValue=areas.value; 
    areas.length=1; 
    if(cityValue=='0') return; 
    if(typeof(cities[cityValue])=='undefined') return; 
    for(i=0; i<cities[cityValue].length; i++){ 
        ii = i+1; 
        areas.options[ii] = new Option(); 
        areas.options[ii].text = cities[cityValue][i]; 
        areas.options[ii].value = cities[cityValue][i]; 
        };
};

//输入框清除信息
function OnFocusFun(element,elementvalue){
  if(element.value==elementvalue){
    element.value="";
    element.style.color="#333";
  };
};
function OnBlurFun(element,elementvalue){
  if(element.value==""||element.value.replace(/\s/g,"")=="")
    {
      element.value=elementvalue;
      element.style.color="#999";
    };
};