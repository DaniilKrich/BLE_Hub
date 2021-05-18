window.addEventListener('load', function (): void {
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

    var root: HTMLUListElement = document.getElementById("Root") as HTMLUListElement;
    var action: HTMLDivElement = document.getElementById("Action") as HTMLDivElement;

    function reqListener() {

    }


    root.addEventListener("click", (e) => {
        if (e.target == null)
            return;
        var el = e.target as HTMLLIElement
        
        if (el.className == 'Characteristic') {

            var xhr: XMLHttpRequest = new XMLHttpRequest();
            xhr.onload = reqListener;
            xhr.open("get", "yourFile.txt", true);
            xhr.send();

            //xhr.setRequestHeader();


            action.innerHTML = el.getAttribute('data');
        }
        if (el.className == 'Hub') {
            action.innerHTML = el.getAttribute('data');
        }
        if (el.className == 'BleSensor'){
            action.innerHTML = el.getAttribute('data');
        }
    });


});