window.addEventListener('load', function () {
    console.log('Document.load');
    var button = document.getElementById('mybtn');
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
//# sourceMappingURL=Site.js.map