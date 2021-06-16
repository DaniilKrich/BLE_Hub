/// <reference path="TreeNode.ts" />

class BleHub extends TreeNode {

    private ScanBleEnvButton: HTMLDivElement;
    private ScanBleResultButton: HTMLDivElement;
    private BleScriptButton: HTMLDivElement;
    private NodeStatisticsButton: HTMLDivElement;

    private description: string;

    // [{"bleHubID":1,"name":"test","description":"test description","bleServers":null}]
    constructor(
        json?: IBleHub
    ) {
        super()
        if (json != null) {
            this.Name = json.name;
            this.ID = json.bleHubID;
            this.description = json.description;
        }


        this.Update = this.update;


        this.ScanBleEnvButton = document.createElement('div') as HTMLDivElement;
        this.ScanBleEnvButton.className = 'Action';
        this.ScanBleEnvButton.innerText = 'Просканировать окружение';
        this.ScanBleEnvButton.onclick = () => this.ScanBleEnvButtonOnclick();

        this.ScanBleResultButton = document.createElement('div') as HTMLDivElement;
        this.ScanBleResultButton.className = 'Action';
        this.ScanBleResultButton.innerText = 'Доступные полевые устройства';
        this.ScanBleResultButton.onclick = this.ScanBleResultButtonOnclick;

        this.BleScriptButton = document.createElement('div') as HTMLDivElement;
        this.BleScriptButton.className = 'Action';
        this.BleScriptButton.innerText = 'Сценарии';
        this.BleScriptButton.onclick = this.BleScriptButtonOnclick;

        this.NodeStatisticsButton = document.createElement('div') as HTMLDivElement;
        this.NodeStatisticsButton.className = 'Action';
        this.NodeStatisticsButton.innerText = 'Статистика';
        this.NodeStatisticsButton.onclick = () => this.NodeStatisticsButtonOnclick();

        this.OnClick = () => this.showActions();
    }




    private update(): void {
        var bleNode: BleNode = new BleNode();
        bleNode.Name = 'Полевое устройство 1';
        this.Append(bleNode);

        //bleNode = new BleNode();
        //bleNode.Name = 'Полевое устройство 2';
        //this.Append(bleNode);

        //bleNode = new BleNode();
        //bleNode.Name = 'Полевое устройство 3';
        //this.Append(bleNode);
    }

    private showActions(): void {
        console.log(this);
        actions.innerHTML = '';
        interfaceZone.innerHTML = '';
        var header: HTMLHeadElement = document.createElement('h1');
        header.textContent = this.Name;
        actions.append(header)



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
    }

    private ScanBleEnvReqListener(req: XMLHttpRequest): void {
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



        var tbl: HTMLTableElement = document.createElement('table');
        var header: HTMLTableRowElement = document.createElement('tr');
        var hmac: HTMLTableHeaderCellElement = document.createElement('th');
        hmac.textContent = 'BLE MAC адрес';
        header.appendChild(hmac);

        var hname: HTMLTableHeaderCellElement = document.createElement('th');
        hname.textContent = 'Имя';
        header.appendChild(hname);

        var hadd: HTMLTableHeaderCellElement = document.createElement('th');
        hadd.textContent = 'Добавить';
        header.appendChild(hadd);

        tbl.appendChild(header);

        var servers: IBleServer[] = JSON.parse(req.responseText);
        for (var i in servers) {
            var srv = servers[i];
            var row: HTMLTableRowElement = document.createElement('tr');
            var mac: HTMLTableDataCellElement = document.createElement('td');
            mac.innerText = srv.bleAdr;
            row.appendChild(mac);
            var name: HTMLTableDataCellElement = document.createElement('td');
            name.innerText = srv.name;
            row.appendChild(name);

            var addbtn: HTMLTableDataCellElement = document.createElement('td');

            var btn: HTMLDivElement = document.createElement('div');
            btn.className = 'Action';
            btn.classList.add('Clickable');
            btn.innerText = '+';
            btn.onclick = () => this.AddServer(srv);
            addbtn.appendChild(btn);
            row.appendChild(addbtn);

            tbl.appendChild(row);
        }

        interfaceZone.appendChild(tbl);
    }

    private AddServer(srv: IBleServer): void {

    }

    private ScanBleEnvButtonOnclick(): void {
        interfaceZone.innerHTML = '';

        var xhr: XMLHttpRequest = new XMLHttpRequest();
        xhr.onload = () => this.ScanBleEnvReqListener(xhr);
        xhr.open('get', '/BleServers/GetScanResults', true);
        xhr.send();
        //xhr.setRequestHeader();
    }

    private ScanBleResultButtonOnclick(): void {
        function reqListener(this: XMLHttpRequest, ev: ProgressEvent<EventTarget>) {
            interfaceZone.innerHTML = this.responseText;
        }

        var xhr: XMLHttpRequest = new XMLHttpRequest();
        xhr.onload = reqListener;
        xhr.open('get', '', true);
        xhr.send();
        //xhr.setRequestHeader();
    }

    private BleScriptButtonOnclick(): void {
        function reqListener(this: XMLHttpRequest, ev: ProgressEvent<EventTarget>) {
            interfaceZone.innerHTML = this.responseText;
        }

        var xhr: XMLHttpRequest = new XMLHttpRequest();
        xhr.onload = reqListener;
        xhr.open('get', '', true);
        //xhr.send();
        //xhr.setRequestHeader();
    }

    private NodeStatisticsButtonListener(req: XMLHttpRequest) {
        interfaceZone.innerHTML = req.responseText;
    }

    private NodeStatisticsButtonOnclick(): void {
        var xhr: XMLHttpRequest = new XMLHttpRequest();
        xhr.onload = () => this.NodeStatisticsButtonListener(xhr);
        xhr.open('get', '/AnalogValues/getvalues?BleCharacteristicID=2', true);
        xhr.send();
        //xhr.setRequestHeader();
    }

}
