var __extends = (this && this.__extends) || (function () {
    var extendStatics = function (d, b) {
        extendStatics = Object.setPrototypeOf ||
            ({ __proto__: [] } instanceof Array && function (d, b) { d.__proto__ = b; }) ||
            function (d, b) { for (var p in b) if (Object.prototype.hasOwnProperty.call(b, p)) d[p] = b[p]; };
        return extendStatics(d, b);
    };
    return function (d, b) {
        if (typeof b !== "function" && b !== null)
            throw new TypeError("Class extends value " + String(b) + " is not a constructor or null");
        extendStatics(d, b);
        function __() { this.constructor = d; }
        d.prototype = b === null ? Object.create(b) : (__.prototype = b.prototype, new __());
    };
})();
var BleCharaceristic = /** @class */ (function (_super) {
    __extends(BleCharaceristic, _super);
    function BleCharaceristic() {
        var _this = _super.call(this) || this;
        _this.className = 'BleCharacteristic';
        return _this;
    }
    return BleCharaceristic;
}(HTMLLIElement));
var BleHub = /** @class */ (function (_super) {
    __extends(BleHub, _super);
    function BleHub() {
        var _this = _super.call(this) || this;
        //<span class="caret hub caret-down">Концентратор 1</span>
        var name = new HTMLSpanElement();
        name.className = 'caret';
        name.textContent = 'Концентратор 1';
        _this.appendChild(name);
        // <ul class="nested active">
        var nodes = new HTMLUListElement();
        nodes.className = 'nested';
        _this.appendChild(nodes);
        return _this;
    }
    BleHub.prototype.GetScan = function () {
    };
    BleHub.prototype.GetNode = function () {
    };
    return BleHub;
}(HTMLLIElement));
var BleNode = /** @class */ (function (_super) {
    __extends(BleNode, _super);
    function BleNode() {
        var _this = _super.call(this) || this;
        _this.className = 'BleNode';
        _this.addEventListener('click', _this.OnClick);
        return _this;
    }
    BleNode.prototype.OnClick = function () {
        this.parentElement
            .querySelector(".nested")
            .classList.toggle("active");
        this.classList.toggle("caret-down");
    };
    return BleNode;
}(HTMLLIElement));
var BleService = /** @class */ (function (_super) {
    __extends(BleService, _super);
    function BleService() {
        return _super !== null && _super.apply(this, arguments) || this;
    }
    return BleService;
}(HTMLLIElement));
var MainTree = /** @class */ (function (_super) {
    __extends(MainTree, _super);
    function MainTree() {
        var _this = _super.call(this) || this;
        //this.addEventListener("click", (e) => {
        //    if (e.target == null)
        //        return;
        //    var el = e.target as HTMLLIElement
        //    if (el.className == 'Characteristic') {
        //        var xhr: XMLHttpRequest = new XMLHttpRequest();
        //        xhr.onload = reqListener;
        //        xhr.open("get", "yourFile.txt", true);
        //        xhr.send();
        //        //xhr.setRequestHeader();
        //        actions.innerHTML = el.getAttribute('data');
        //    }
        //if (el.className == 'Hub') {
        //    actions.innerHTML = el.getAttribute('data');
        //}
        //if (el.className == 'BleSensor') {
        //    actions.innerHTML = el.getAttribute('data');
        //}
        //});
        _this.Update();
        return _this;
    }
    MainTree.prototype.Update = function () {
        /*this.BleHubs = new*/
        //var list: HTMLLIElement = new HTMLLIElement();
        /*
          <span class="caret caret-down">Сервер</span>
            <ul class="nested active">
         */
        this.innerHTML = '';
        var server = new Server();
        this.appendChild(server);
        var xhr = new XMLHttpRequest();
        xhr.onload = this.FillBleHubs;
        xhr.open("get", "/Home/GetBleHubs", true);
        xhr.send();
        //xhr.setRequestHeader();
        //actions.innerHTML = el.getAttribute('data');
    };
    MainTree.prototype.FillBleHubs = function () {
        var msg = 'ok!';
        alert(msg);
    };
    return MainTree;
}(HTMLUListElement));
var Server = /** @class */ (function (_super) {
    __extends(Server, _super);
    function Server() {
        var _this = _super.call(this) || this;
        // <span class="caret caret-down" > Сервер < /span>
        var name = new HTMLSpanElement();
        name.className = 'caret';
        name.textContent = 'Сервер';
        _this.appendChild(name);
        // <ul class="nested active" >
        var nodes = new HTMLUListElement();
        nodes.className = 'nested';
        _this.appendChild(nodes);
        //<span class="caret BleSensor" data = "полевое устройство" > Полевое устройство 1 < /span>
        /*
                    */
        _this.addEventListener('click', _this.OnClick);
        return _this;
    }
    Server.prototype.OnClick = function () {
        this.parentElement
            .querySelector(".nested")
            .classList.toggle("active");
        this.classList.toggle("caret-down");
    };
    return Server;
}(HTMLLIElement));
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
    //var toggler = document.getElementsByClassName("caret");
    //var i;
    //for (i = 0; i < toggler.length; i++) {
    //    toggler[i].addEventListener("click", function () {
    //        this.parentElement.querySelector(".nested").classList.toggle("active");
    //        this.classList.toggle("caret-down");
    //    });
    //}
    var root = document.getElementById("Root");
    root.Update();
    var actions = document.getElementById("Actions");
});
//# sourceMappingURL=site.js.map