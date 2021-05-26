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
var TreeNode = /** @class */ (function () {
    function TreeNode() {
        this.children = [];
        this.container = document.createElement('ul');
        this.title = document.createElement('span');
        this.nodeWrapper = document.createElement('li');
        // <span class="caret caret-down" > Сервер < /span>
        this.title = document.createElement('span');
        this.title.className = 'caret';
        this.title.addEventListener('click', this.OnClick);
        this.nodeWrapper.appendChild(this.title);
        // <ul class="nested active" >
        this.container.className = 'nested';
        this.nodeWrapper.appendChild(this.container);
    }
    Object.defineProperty(TreeNode.prototype, "Node", {
        /** li element to insert into parent ul*/
        get: function () {
            return this.nodeWrapper;
        },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(TreeNode.prototype, "Name", {
        get: function () {
            return this.title.textContent;
        },
        set: function (name) {
            if (this.IsNullOrWhiteSpace(this.title.textContent)) {
                if (this.Update)
                    this.Update();
            }
            else {
                if (this.Rename)
                    this.Rename();
            }
            this.title.textContent = name;
        },
        enumerable: false,
        configurable: true
    });
    TreeNode.prototype.Append = function (node) {
        node.parent = this;
        this.children.push(node);
        this.container.appendChild(node.Node);
    };
    TreeNode.prototype.IsNullOrWhiteSpace = function (str) {
        return str === null || str.match(/^\s*$/) !== null;
    };
    TreeNode.prototype.OnClick = function (ev) {
        this.parentElement
            .querySelector(".nested")
            .classList.toggle("active");
        this.classList.toggle("caret-down");
    };
    return TreeNode;
}());
/// <reference path="TreeNode.ts" />
var BleCharaceristic = /** @class */ (function (_super) {
    __extends(BleCharaceristic, _super);
    function BleCharaceristic() {
        return _super.call(this) || this;
    }
    return BleCharaceristic;
}(TreeNode));
/// <reference path="TreeNode.ts" />
var BleHub = /** @class */ (function (_super) {
    __extends(BleHub, _super);
    function BleHub() {
        var _this = _super.call(this) || this;
        _this.Update = _this.update;
        return _this;
    }
    BleHub.prototype.update = function () {
        var bleNode = new BleNode();
        bleNode.Name = 'Полевое устройство 1';
        this.Append(bleNode);
        bleNode = new BleNode();
        bleNode.Name = 'Полевое устройство 2';
        this.Append(bleNode);
        bleNode = new BleNode();
        bleNode.Name = 'Полевое устройство 3';
        this.Append(bleNode);
    };
    BleHub.prototype.GetScan = function () {
    };
    BleHub.prototype.GetNode = function () {
    };
    return BleHub;
}(TreeNode));
/// <reference path="TreeNode.ts" />
var BleNode = /** @class */ (function (_super) {
    __extends(BleNode, _super);
    function BleNode() {
        var _this = _super.call(this) || this;
        _this.Update = _this.update;
        return _this;
    }
    BleNode.prototype.update = function () {
        var bleService = new BleService();
        bleService.Name = 'Почва';
        this.Append(bleService);
        bleService = new BleService();
        bleService.Name = 'Атмосфера';
        this.Append(bleService);
    };
    return BleNode;
}(TreeNode));
var BleService = /** @class */ (function (_super) {
    __extends(BleService, _super);
    function BleService() {
        var _this = _super.call(this) || this;
        _this.Update = _this.update;
        return _this;
    }
    BleService.prototype.update = function () {
        var bleCharaceristic = new BleCharaceristic();
        bleCharaceristic.Name = 'Температура';
        this.Append(bleCharaceristic);
        bleCharaceristic = new BleCharaceristic();
        bleCharaceristic.Name = 'Влажность';
        this.Append(bleCharaceristic);
    };
    return BleService;
}(TreeNode));
var MainTree = /** @class */ (function () {
    function MainTree(root) {
        //this.addEventListener("click", (e) => {
        //    if (e.target == null)
        //        return;
        //    var el = e.target as HTMLLIElement
        this.root = root;
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
        this.Update();
    }
    MainTree.prototype.Update = function () {
        this.root.innerHTML = '';
        this.tree = document.createElement('ul');
        this.tree.id = 'Tree';
        this.root.appendChild(this.tree);
        /*this.BleHubs = new*/
        //var list: HTMLLIElement = new HTMLLIElement();
        /*
          <span class="caret caret-down">Сервер</span>
            <ul class="nested active">
         */
        var server = new Server(this.tree);
        server.Name = 'Сервер';
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
}());
/// <reference path="TreeNode.ts" />
var Server = /** @class */ (function (_super) {
    __extends(Server, _super);
    function Server(parentContainer) {
        var _this = _super.call(this) || this;
        parentContainer.appendChild(_this.Node);
        _this.Update = _this.update;
        return _this;
    }
    Server.prototype.update = function () {
        var bleHub = new BleHub();
        bleHub.Name = 'Концентратор 1';
        this.Append(bleHub);
        bleHub = new BleHub();
        bleHub.Name = 'Концентратор 2';
        this.Append(bleHub);
        var bleHub = new BleHub();
        bleHub.Name = 'Концентратор 3';
        this.Append(bleHub);
    };
    return Server;
}(TreeNode));
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
    var root = document.getElementById('Root');
    var tree = new MainTree(root);
    var actions = document.getElementById("Actions");
});
//# sourceMappingURL=site.js.map