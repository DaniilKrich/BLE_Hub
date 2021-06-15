/// <reference path="TreeNode.ts" />

class BleHub extends TreeNode {

    private ScanBleEnvButton: HTMLDivElement;
    private ScanBleResultButton: HTMLDivElement;
    private BleScriptButton: HTMLDivElement;
    private NodeStatisticsButton: HTMLDivElement;

    constructor() {

        super()
        this.Update = this.update;

        this.OnClick = this.showActions;

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
        //addnodesbutton
        this.ScanBleEnvButton = document.createElement('div') as HTMLDivElement;
        this.ScanBleEnvButton.className = 'Action';
        this.ScanBleEnvButton.innerText = 'Просканировать окружение';
        this.ScanBleEnvButton.onclick = this.ScanBleEnvButtonOnclick;
        actions.append(this.ScanBleEnvButton);
        //
        this.ScanBleResultButton = document.createElement('div') as HTMLDivElement;
        this.ScanBleResultButton.className = 'Action';
        this.ScanBleResultButton.innerText = 'Доступные полевые устройства';
        this.ScanBleResultButton.onclick = this.ScanBleResultButtonOnclick;
        actions.append(this.ScanBleResultButton);
        //
        this.BleScriptButton = document.createElement('div') as HTMLDivElement;
        this.BleScriptButton.className = 'Action';
        this.BleScriptButton.innerText = 'Сценарии';
        this.BleScriptButton.onclick = this.BleScriptButtonOnclick;
        actions.append(this.BleScriptButton);
        //
        this.NodeStatisticsButton = document.createElement('div') as HTMLDivElement;
        this.NodeStatisticsButton.className = 'Action';
        this.NodeStatisticsButton.innerText = 'Статистика';
        this.NodeStatisticsButton.onclick = this.NodeStatisticsButtonOnclick;
        actions.append(this.NodeStatisticsButton);
        //
        //this.container.classList.toggle("active");
        //this.title.classList.toggle("caret-down");
    }

    private ScanBleEnvButtonOnclick(): void {
        function reqListener(this: XMLHttpRequest, ev: ProgressEvent<EventTarget>) {
            interfaceZone.innerHTML = this.responseText;
        }

        var xhr: XMLHttpRequest = new XMLHttpRequest();
        xhr.onload = reqListener;
        xhr.open('get', '', true);
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
        xhr.send();
        //xhr.setRequestHeader();
    }

    private NodeStatisticsButtonOnclick(): void {
        function reqListener(this: XMLHttpRequest, ev: ProgressEvent<EventTarget>) {
            interfaceZone.innerHTML = this.responseText;
        }

        var xhr: XMLHttpRequest = new XMLHttpRequest();
        xhr.onload = reqListener;
        xhr.open('get', '', true);
        xhr.send();
        //xhr.setRequestHeader();
    }

}
