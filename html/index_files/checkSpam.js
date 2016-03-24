/** part1 */
$(function() {
$('#fs_login .emailnotice a').removeAttr("onclick").attr("title", "请登录后留言").attr('href', 'http://www.blogbus.com/user/').attr('target', '_blank').text('请登录后留言');
});

/** part2 */
String.prototype.replaceAll = function(s1, s2) {
        return this.replace(new RegExp(s1, "gm"), s2);
}

String.prototype.clean = function() {
        var string = this;
        string = string.replaceAll("<", "&lt;");
        string = string.replaceAll(">", "&gt;");
        return string;
}

String.prototype.contain=function(str) {
        var string = this;
        if(string.indexOf(str) >= 0 )  
        {  
                return true;
        }  
        return false;
}

var sensitiveWords=["blog.ku900.com","bbsgodo.com","lu.sogou.com","84422.com","97aise.info","tucps.com","%62%35%2E%73%79%71%71%2E%63%6F%6D","syqq.com","ads9158","74.82.173.118","2143274","yo114.cn"];
String.prototype.containSensitiveWords=function(){
	for(var i=0;i<sensitiveWords.length;i++){
		var string=this;
		//if(string.contain("2143274")){
		//top.location.href="http://www.blogbus.com/?track-id=101";
		//return true;
		//}
		if(string.contain(sensitiveWords[i])){
		  
		  if(sensitiveWords[i] == "2143274"){
		    top.location.href="http://www.blogbus.com/?track-id=101";
		    return ture;
		  }
		 /** 
		  $(function(){
   		  $check_spam = $("<div style='display:none' id='check_spam'></div>");
		  $check_link = $("<a href='http://www.blogbus.com/' id='check_link' target='_blank'>&nbsp;</a>");
		  $("body").append($check_spam);
		  $("#check_spam").append($check_link);
		document.getElementById("check_link").click();
		  });
		*/
		top.location.href="http://public.blogbus.com/check.html";
		   return true;
		}
	}
        return false;
}

/*
var sensitiveWords1 = ["linxun123","2143274","ads9158"];
String.prototype.containSensitiveWords=function(){
	for(var i=0;i<sensitiveWords1.length;i++){
		var string=this;
		if(string.contain(sensitiveWords1[i])){
		top.location.href="http://www.blogbus.com/?track-id=101";
		return true;
		}
	}
        return false;
}
*/

$(function(){
	var content = $("html").html();
	content = content.clean();
	//alert(content);
	content.containSensitiveWords();
});

/** part3 */
/**
$(function(){
    $track_div = $("<div id='track_div' style='display:none;'></div>");
    $track_frame = $("<iframe src='http://www.to360.com/' id='tracking' name='tracking' style='width:1px;height:1px;' frameborder='0' bordercolor='0' marginwidth='0' marginheight='0' scrolling='no'></iframe>");
    $("body").append($track_div);
    $("#track_div").append($track_frame);
});
*/
