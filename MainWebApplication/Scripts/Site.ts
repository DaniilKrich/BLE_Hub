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

    //var toggler = document.getElementsByClassName("caret");
    //var i;

    //for (i = 0; i < toggler.length; i++) {
    //    toggler[i].addEventListener("click", function () {
    //        this.parentElement.querySelector(".nested").classList.toggle("active");
    //        this.classList.toggle("caret-down");
    //    });
    //}
    var tree: HTMLDivElement = document.getElementById('Tree') as HTMLDivElement;
    var root: MainTree = <MainTree>(<unknown> document.createElement('div'));
    tree.innerHTML = '';
    tree.appendChild(root);

    //root.Update();

    var actions: HTMLDivElement = document.getElementById("Actions") as HTMLDivElement;


    

});