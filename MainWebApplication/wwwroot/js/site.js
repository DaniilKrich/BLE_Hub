window.addEventListener('load', function () {
    console.log('Document.load');
    //var button: HTMLButtonElement = document.getElementById('mybtn') as HTMLButtonElement;
    //console.log(button);
    //button.addEventListener('click', function () {
    //    console.log('Button!');
    //    document.body.classList.toggle('dark-theme');
    //    var className = document.body.className;
    //    if (className == "light-theme") {
    //        this.textContent = "Dark";
    //    }
    //    else {
    //        this.textContent = "Light";
    //    }
    //    console.log('current class name: ' + className);
    //});
    var toggler = document.getElementsByClassName("caret");
    var i;
    for (i = 0; i < toggler.length; i++) {
        toggler[i].addEventListener("click", function () {
            this.parentElement.querySelector(".nested").classList.toggle("active");
            this.classList.toggle("caret-down");
        });
    }
    var root = document.getElementById("Root");
    var action = document.getElementById("Action");
    function reqListener() {
    }
    root.addEventListener("click", function (e) {
        if (e.target == null)
            return;
        var el = e.target;
        if (el.className == 'Characteristic') {
            var xhr = new XMLHttpRequest();
            xhr.onload = reqListener;
            xhr.open("get", "yourFile.txt", true);
            xhr.send();
            //xhr.setRequestHeader();
            action.innerHTML = el.getAttribute('data');
        }
        if (el.className == 'Hub') {
            action.innerHTML = el.getAttribute('data');
        }
        if (el.className == 'BleSensor') {
            action.innerHTML = el.getAttribute('data');
        }
    });
});
//# sourceMappingURL=Site.js.map