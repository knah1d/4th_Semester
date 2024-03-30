/* 
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


var editor = null;
var lan = null;
var codes = "";
function reset(){
    if (null != editor) {
        //var code = editor.getValue();
        $('#chtml').remove();
        var mode = editor.session.$modeId;
        mode = mode.substr(mode.lastIndexOf('/') + 1);
        $('#editor').after('<pre class="prettyprint" data-lan="' + mode + '"><code>' + codes + '</code></pre>');
        $('#editor').remove();
        editor.destroy();
        try {
            $('#console').remove();
            $('.try_it').show();
            $('.compile-btn').remove();
            $('pre').addClass('prettyprint');
            editor.destroy();
            $('#editor').removeAttr('id');
        } catch (e) {
        }
    }
    $('.reset-btn').remove();
}

$(function(){
    
    $('body').append('<div id="loader" style="display:none;position:fixed;z-index:99999;top:0;bottom:0left:0;right:0;background-color:rgba(10,10,10,0.3);width:100%;height:100%;"><img style="position:absolute;top:0;left:0; right:0;bottom:0;margin:auto; " src="https://www.tutorialcup.com/loader.gif" /></div>');
    
    
    
});


$(document).on('click','.try_it',function(e){
	
    e.preventDefault();
    
    reset();
    
    codes = $(this).closest('.code').find('pre').find('code').html();
    $(this).hide();
    $(this).closest('.code').find('pre').attr('id','editor');
    var $pre = $('#editor');
    $pre.removeClass('prettyprint');
    $pre.after('<p id="console"></p>');
    var chtml = '<input type="checkbox" onchange="{if($(this).is(\':checked\')){$(\'#custom_input\').show();}else{$(\'#custom_input\').hide();}  }" id="cst_in">&nbsp;Custom Input<br>'+
                '<textarea placeholder="Hit enter after each input" id="custom_input" style="display:none;width: 226px; height: 138px; resize: none;"></textarea>'
    $pre.after('<div id="chtml">'+chtml+'</div>');
    
    lan = $.trim($('#editor').attr('data-lan')).toLowerCase();
    	
    $(this).after('<a href="javascript:void(0);" style="float:right;margin-right:5px;" class="btn btn-success compile-btn" data-lan="'+lan+'" >Compile/Run</a><br>');
    $(this).after('<a href="javascript:void(0);" style="float:right;" class="btn btn-success reset-btn" data-lan="'+lan+'" >Reset</a>');
	
	
    
    
    
    editor = ace.edit("editor");
    editor.setOptions({
         maxLines: Infinity,
         minLines:12
    });
    editor.setTheme("ace/theme/chaos");
    editor.session.setMode('ace/mode/'+lan);
    
    
});


$(document).on('click','.compile-btn',function(e){
    e.preventDefault();
    $("#console").html('');
    var code =  editor.getValue();
    $('#loader').show();
    var option = {'code':code,'lan':lan};
        
        if($('#cst_in').is(":checked") && $.trim($('#custom_input').val()).length>0){
            option["input"]= $.trim($('#custom_input').val());
            
        }
    
    $.ajax({
		 url:'https://www.tutorialcup.com/cros-prevent.php',
		 type:'post',
		 data:option,
		 success:function(res, textStatus, jqXHR){
                                $('#loader').hide();
				if(res.indexOf('error::::')!=-1){
				  $('#console').html('<strong style="color:#e22e71;" >Errors:</strong><br /><span style="color:#e22e71;">'+res.replace(/error::::/gi,"").replace(/\n/gi,"<br />")+'</span>');
						
				}else{
					 $('#console').html('<strong style="color:#47a447;" >Output:</strong><br />'+res.replace(/\n/gi,"<br />"));
				} 
		 },
		error: function (responseData, textStatus, errorThrown) {
                    $('#loader').hide();
                    alert('Some network error !!!!');
		}
	 
	});
    
});


$(document).on('click','.reset-btn',function(e){
    e.preventDefault();
    reset();
});

