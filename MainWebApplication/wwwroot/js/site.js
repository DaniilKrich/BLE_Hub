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
var TreeElement = /** @class */ (function () {
    function TreeElement() {
        this.title = document.createElement('span');
        // <span class="caret caret-down" > Сервер < /span>
        //this.title = <HTMLSpanElement>document.createElement('span');
        this.title.classList.add('Clickable');
    }
    Object.defineProperty(TreeElement.prototype, "Node", {
        /** li element to insert into parent ul*/
        get: function () {
            return this.nodeWrapper;
        },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(TreeElement.prototype, "ID", {
        get: function () {
            return this.title.attributes['dbid'];
        },
        set: function (id) {
            this.title.attributes['dbid'] = id;
        },
        enumerable: false,
        configurable: true
    });
    Object.defineProperty(TreeElement.prototype, "Name", {
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
    TreeElement.prototype.IsNullOrWhiteSpace = function (str) {
        return str === null || str.match(/^\s*$/) !== null;
    };
    Object.defineProperty(TreeElement.prototype, "OnClick", {
        set: function (f) {
            this.title.addEventListener('click', f);
        },
        enumerable: false,
        configurable: true
    });
    return TreeElement;
}());
/// <reference path="TreeElement.ts" />
var TreeLeaf = /** @class */ (function (_super) {
    __extends(TreeLeaf, _super);
    function TreeLeaf() {
        var _this = _super.call(this) || this;
        _this.children = [];
        _this.nodeWrapper = document.createElement('li');
        _this.title.className = 'Characteristic';
        _this.nodeWrapper.appendChild(_this.title);
        var t = _this;
        _this.OnClick = function () { return t.onClick(); };
        return _this;
    }
    TreeLeaf.prototype.onClick = function () {
        var msg = ': ok!';
        alert(this.Name + msg);
    };
    return TreeLeaf;
}(TreeElement));
/// <reference path="TreeLeaf.ts" />
var BleCharaceristic = /** @class */ (function (_super) {
    __extends(BleCharaceristic, _super);
    function BleCharaceristic() {
        return _super.call(this) || this;
    }
    return BleCharaceristic;
}(TreeLeaf));
/// <reference path="TreeElement.ts" />
var TreeNode = /** @class */ (function (_super) {
    __extends(TreeNode, _super);
    function TreeNode() {
        var _this = _super.call(this) || this;
        _this.children = [];
        _this.nodeWrapper = document.createElement('li');
        _this.title.className = 'caret';
        _this.nodeWrapper.appendChild(_this.title);
        // <ul class="nested active" >
        _this.container = document.createElement('ul');
        _this.container.className = 'nested';
        _this.nodeWrapper.appendChild(_this.container);
        var t = _this;
        _this.OnClick = function () { return t.onClick(); };
        return _this;
    }
    TreeNode.prototype.Append = function (node) {
        node.parent = this;
        this.children.push(node);
        this.container.appendChild(node.Node);
    };
    TreeNode.prototype.onClick = function () {
        this.container.classList.toggle("active");
        this.title.classList.toggle("caret-down");
    };
    return TreeNode;
}(TreeElement));
/// <reference path="TreeNode.ts" />
var BleHub = /** @class */ (function (_super) {
    __extends(BleHub, _super);
    // [{"bleHubID":1,"name":"test","description":"test description","bleServers":null}]
    function BleHub(json) {
        var _this = _super.call(this) || this;
        if (json != null) {
            _this.Name = json.name;
            _this.ID = json.bleHubID;
            _this.description = json.description;
        }
        _this.Update = _this.update;
        _this.ScanBleEnvButton = document.createElement('div');
        _this.ScanBleEnvButton.className = 'Action';
        _this.ScanBleEnvButton.innerText = 'Просканировать окружение';
        _this.ScanBleEnvButton.onclick = function () { return _this.ScanBleEnvButtonOnclick(); };
        _this.ScanBleResultButton = document.createElement('div');
        _this.ScanBleResultButton.className = 'Action';
        _this.ScanBleResultButton.innerText = 'Доступные полевые устройства';
        _this.ScanBleResultButton.onclick = _this.ScanBleResultButtonOnclick;
        _this.BleScriptButton = document.createElement('div');
        _this.BleScriptButton.className = 'Action';
        _this.BleScriptButton.innerText = 'Сценарии';
        _this.BleScriptButton.onclick = _this.BleScriptButtonOnclick;
        _this.NodeStatisticsButton = document.createElement('div');
        _this.NodeStatisticsButton.className = 'Action';
        _this.NodeStatisticsButton.innerText = 'Статистика';
        _this.NodeStatisticsButton.onclick = function () { return _this.NodeStatisticsButtonOnclick(); };
        _this.OnClick = function () { return _this.showActions(); };
        return _this;
    }
    BleHub.prototype.update = function () {
        var bleNode = new BleNode();
        bleNode.Name = 'Полевое устройство 1';
        this.Append(bleNode);
        //bleNode = new BleNode();
        //bleNode.Name = 'Полевое устройство 2';
        //this.Append(bleNode);
        //bleNode = new BleNode();
        //bleNode.Name = 'Полевое устройство 3';
        //this.Append(bleNode);
    };
    BleHub.prototype.showActions = function () {
        console.log(this);
        actions.innerHTML = '';
        interfaceZone.innerHTML = '';
        var header = document.createElement('h1');
        header.textContent = this.Name;
        actions.append(header);
        //addnodesbutton
        actions.append(this.ScanBleEnvButton);
        //
        actions.append(this.ScanBleResultButton);
        //
        actions.append(this.BleScriptButton);
        //
        actions.append(this.NodeStatisticsButton);
        //
        //this.container.classList.toggle("active");
        //this.title.classList.toggle("caret-down");
    };
    BleHub.prototype.ScanBleEnvReqListener = function (req) {
        /*
        [
            {
                "bleServerID":0,
                "bleHub":null,
                "bleServices":null,
                "bleAdr":"C4:4F:33:7F:CB:9B",
                "name":"\u041F\u043E\u043B\u0435\u0432\u043E\u0435 \u0443\u0441\u0442\u0440\u043E\u0439\u0441\u0442\u0432\u043E c4:4f:33:7f:cb:9b"
            },
            {
                "bleServerID":0,
                "bleHub":null,
                "bleServices":null,
                "bleAdr":"54:EF:A7:D1:23:19",
                "name":"Beacon"
            },
            {
                "bleServerID":0,
                "bleHub":null,
                "bleServices":null,
                "bleAdr":"D1:61:83:9F:A4:20",
                "name":""
            }
        ]
         
          */
        var _this = this;
        var tbl = document.createElement('table');
        var header = document.createElement('tr');
        var hmac = document.createElement('th');
        hmac.textContent = 'BLE MAC адрес';
        header.appendChild(hmac);
        var hname = document.createElement('th');
        hname.textContent = 'Имя';
        header.appendChild(hname);
        var hadd = document.createElement('th');
        hadd.textContent = 'Добавить';
        header.appendChild(hadd);
        tbl.appendChild(header);
        var servers = JSON.parse(req.responseText);
        for (var i in servers) {
            var srv = servers[i];
            var row = document.createElement('tr');
            var mac = document.createElement('td');
            mac.innerText = srv.bleAdr;
            row.appendChild(mac);
            var name = document.createElement('td');
            name.innerText = srv.name;
            row.appendChild(name);
            var addbtn = document.createElement('td');
            var btn = document.createElement('div');
            btn.className = 'Action';
            btn.classList.add('Clickable');
            btn.innerText = '+';
            btn.onclick = function () { return _this.AddServer(srv); };
            addbtn.appendChild(btn);
            row.appendChild(addbtn);
            tbl.appendChild(row);
        }
        interfaceZone.appendChild(tbl);
    };
    BleHub.prototype.AddServer = function (srv) {
    };
    BleHub.prototype.ScanBleEnvButtonOnclick = function () {
        var _this = this;
        interfaceZone.innerHTML = '';
        var xhr = new XMLHttpRequest();
        xhr.onload = function () { return _this.ScanBleEnvReqListener(xhr); };
        xhr.open('get', '/BleServers/GetScanResults', true);
        xhr.send();
        //xhr.setRequestHeader();
    };
    BleHub.prototype.ScanBleResultButtonOnclick = function () {
        function reqListener(ev) {
            interfaceZone.innerHTML = this.responseText;
        }
        var xhr = new XMLHttpRequest();
        xhr.onload = reqListener;
        xhr.open('get', '', true);
        xhr.send();
        //xhr.setRequestHeader();
    };
    BleHub.prototype.BleScriptButtonOnclick = function () {
        function reqListener(ev) {
            interfaceZone.innerHTML = this.responseText;
        }
        var xhr = new XMLHttpRequest();
        xhr.onload = reqListener;
        xhr.open('get', '', true);
        //xhr.send();
        //xhr.setRequestHeader();
    };
    BleHub.prototype.NodeStatisticsButtonListener = function (req) {
        interfaceZone.innerHTML = req.responseText;
    };
    BleHub.prototype.NodeStatisticsButtonOnclick = function () {
        var _this = this;
        var xhr = new XMLHttpRequest();
        xhr.onload = function () { return _this.NodeStatisticsButtonListener(xhr); };
        xhr.open('get', '/AnalogValues/getvalues?BleCharacteristicID=2', true);
        xhr.send();
        //xhr.setRequestHeader();
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
        //xhr.send();
        //xhr.setRequestHeader();
        //actions.innerHTML = el.getAttribute('data');
    };
    MainTree.prototype.FillBleHubs = function () {
        var msg = 'ok!';
        alert(msg);
    };
    return MainTree;
}());
var TreeRoot = /** @class */ (function (_super) {
    __extends(TreeRoot, _super);
    function TreeRoot(parentContainer) {
        var _this = _super.call(this) || this;
        _this.children = [];
        _this.nodeWrapper = parentContainer;
        _this.nodeWrapper.appendChild(_this.title);
        // <ul class="nested active" >
        _this.container = document.createElement('ul');
        _this.container.className = 'nested active';
        _this.nodeWrapper.appendChild(_this.container);
        _this.OnClick = _this.onClick;
        return _this;
    }
    TreeRoot.prototype.Append = function (node) {
        node.parent = this;
        this.children.push(node);
        this.container.appendChild(node.Node);
    };
    TreeRoot.prototype.onClick = function (ev) {
        console.log(this);
        //this.parentElement
        //    .querySelector(".nested")
        //    .classList.toggle("active");
        //this.classList.toggle("caret-down");
    };
    return TreeRoot;
}(TreeElement));
/// <reference path="TreeRoot.ts" />
var Server = /** @class */ (function (_super) {
    __extends(Server, _super);
    function Server(parentContainer) {
        var _this = _super.call(this, parentContainer) || this;
        _this.AddBleHubButton = document.createElement('div');
        _this.AddBleHubForm = document.createElement('form');
        _this.AddBleHubButton.className = 'Action';
        _this.AddBleHubButton.classList.add('Clickable');
        _this.AddBleHubButton.innerText = 'Добавление концентратора';
        _this.AddBleHubButton.onclick = function () { return _this.AddBleHubButtonOnclick(); };
        // <form >
        //    <div class="form-group">
        //    </div>
        //<input name="__RequestVerificationToken"
        //type="hidden"
        //value="CfDJ8PrUNlfFZ9tAh7ylCV1SUXOTUxRGeEysMlr1-0wggkc0CDm_oVujbo2VLfGxSmfRnkFkRwBMwzIuxHRphcLlT69xWrh_O5dUtQdunI4uBhs26IkpCNaAQpBtA8kWCj9-kzi9pYVomuU7v4s-47Wnbx0"></form>
        _this.AddBleHubForm.innerHTML =
            '<div class="form-group">\
                <label class="control-label" for="Name">Сетевое имя</label>\
                <input class="form-control" type="text" id="Name" name="Name" value="">\
                <span class="text-danger field - validation - valid" data-valmsg-for="Name" data-valmsg-replace="true">\
                </span>\
            </div>\
            <input type="submit" value="Добавить" class="btn btn-primary">';
        //        <input type="submit" value="Добавить" class="btn btn-primary">
        //var submit: HTMLInputElement = document.createElement('input');
        //submit.className = 'btn';
        //submit.classList.add('btn-primary');
        //submit.onclick = () => this.CreateBleHub();
        //this.AddBleHubForm.appendChild(submit);
        var cr = function () { return _this.CreateBleHub(); };
        _this.AddBleHubForm.addEventListener("submit", function (event) {
            event.preventDefault();
            cr();
        });
        _this.Update = _this.update;
        _this.OnClick = function () { return _this.showActions(); };
        return _this;
    }
    Server.prototype.updateReqListener = function (req) {
        //var bleHub: BleHub = new BleHub();
        //bleHub.Name = 'Концентратор 1';
        //this.Append(bleHub);
        do {
            var tmp = this.children.pop();
        } while (this.children.length > 0);
        this.container.innerHTML = '';
        var json = JSON.parse(req.response);
        for (var hub in json) {
            var bleHub = new BleHub(json[hub]);
            this.Append(bleHub);
        }
    };
    Server.prototype.update = function () {
        var _this = this;
        var xhr = new XMLHttpRequest();
        xhr.onload = function () { return _this.updateReqListener(xhr); };
        xhr.open('get', '/BleHubs/GetList', true);
        xhr.send();
        //bleHub = new BleHub();
        //bleHub.Name = 'Концентратор 2';
        //this.Append(bleHub);
        //var bleHub: BleHub = new BleHub();
        //bleHub.Name = 'Концентратор 3';
        //this.Append(bleHub);
    };
    Server.prototype.showActions = function () {
        console.log(this);
        actions.innerHTML = '';
        interfaceZone.innerHTML = '';
        var header = document.createElement('h1');
        header.textContent = this.Name;
        actions.append(header);
        actions.append(this.AddBleHubButton);
    };
    Server.prototype.AddBleHubButtonOnclick = function () {
        interfaceZone.innerHTML = '';
        interfaceZone.append(this.AddBleHubForm);
    };
    Server.prototype.CreateBleHubReqListener = function (req) {
        interfaceZone.innerHTML = req.responseText;
        this.Update();
    };
    Server.prototype.CreateBleHub = function () {
        var _this = this;
        var xhr = new XMLHttpRequest();
        var fd = new FormData(this.AddBleHubForm);
        xhr.onload = function () { return _this.CreateBleHubReqListener(xhr); };
        //action = "/BleHubs/Create" method = "post"
        xhr.open('post', '/BleHubs/CreateFnc', true);
        xhr.send(fd);
        //xhr.setRequestHeader();
    };
    return Server;
}(TreeRoot));
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
    var server = new Server(root);
    server.Name = 'Сервер';
    actions = document.getElementById("Actions");
    interfaceZone = document.getElementById("Interface");
});
/// <reference path="IBleHub.ts" />
/// <reference path="IBleService.ts" />
//# sourceMappingURL=site.js.map