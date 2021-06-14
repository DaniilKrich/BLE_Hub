/// <reference path="TreeNode.ts" />

class BleHub extends TreeNode {

    private ScunBleEnvButton: HTMLDivElement;
    private ScunBleResultButton: HTMLDivElement;
    private BleScriptButton: HTMLDivElement;
    private NodeStatisticsButton: HTMLDivElement;

    constructor() {

        super()
        this.Update = this.update;

        this.OnClick = this.onClick;

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

    private onClick(): void {
        console.log(this);
        actions.innerHTML = '';
        //addnodesbutton
        this.ScunBleEnvButton = document.createElement('div') as HTMLDivElement;
        this.ScunBleEnvButton.className = 'Action';
        this.ScunBleEnvButton.innerText = 'Просканировать окружение';
        this.ScunBleEnvButton.onclick = this.ScunBleEnvButtonOnclick;
        actions.append(this.ScunBleEnvButton);
        //
        this.ScunBleResultButton = document.createElement('div') as HTMLDivElement;
        this.ScunBleResultButton.className = 'Action';
        this.ScunBleResultButton.innerText = 'Доступные полевые устройства';
        this.ScunBleResultButton.onclick = this.ScunBleResultButtonOnclick;
        actions.append(this.ScunBleResultButton);
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
        this.container.classList.toggle("active");
        this.title.classList.toggle("caret-down");
    }

    private ScunBleEnvButtonOnclick(): void {
        function reqListener(this: XMLHttpRequest, ev: ProgressEvent<EventTarget>) {
            interfaceZone.innerHTML = this.responseText;
        }

        var xhr: XMLHttpRequest = new XMLHttpRequest();
        xhr.onload = reqListener;
        xhr.open('get', '', true);
        xhr.send();
        //xhr.setRequestHeader();
    }

    private ScunBleResultButtonOnclick(): void {
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
