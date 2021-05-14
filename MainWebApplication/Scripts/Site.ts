window.addEventListener('load', function (): void {
    console.log('Document.load');

    var button: HTMLButtonElement = document.getElementById('mybtn') as HTMLButtonElement;
    console.log(button);

    button.addEventListener('click', function () {
        console.log('Button!');


        document.body.classList.toggle('dark-theme');
        var className = document.body.className;
        if (className == "light-theme") {
            this.textContent = "Dark";
        }
        else {
            this.textContent = "Light";
        }
        console.log('current class name: ' + className);
    });
});