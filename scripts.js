function openTab(event, tab){
    var tabcontent = document.getElementsByClassName("tabcontent");
    var tablinks = document.getElementsByClassName("tablinks");
    var tabNum = 0;
    //show "tab" tab and hide others
    for(var i = 0; i < tabcontent.length; i++){
        if(tabcontent[i].id == tab){
            tabcontent[i].style.display = "block";
        }else{
            tabcontent[i].style.display = "none";
        }
    }

    //show "tab" button as active and make others inactive
    for(var i = 0; i < tablinks.length; i++){
        tablinks[i].className = tablinks[i].className.replace(" active", "");
    }
    event.currentTarget.className += " active";
}