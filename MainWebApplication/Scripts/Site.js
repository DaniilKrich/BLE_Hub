window.addEventListener("load", function () {
    var switcher = document.getElementsByClassName('.btn')[0];
    switcher.addEventListener('click', function () {
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