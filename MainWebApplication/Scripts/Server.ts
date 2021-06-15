/// <reference path="TreeRoot.ts" />

class Server extends TreeRoot {
    private AddBleHubButton: HTMLDivElement = document.createElement('div') as HTMLDivElement;


    constructor(
        parentContainer: HTMLElement
    ) {
        super(parentContainer);

        this.AddBleHubButton.className = 'Action';
        this.AddBleHubButton.classList.add('Clickable');
        this.AddBleHubButton.innerText = 'Добавление концентратора';
        this.AddBleHubButton.onclick = this.AddBleHubButtonOnclick;

        this.Update = this.update;
        this.OnClick = ()=> this.showActions();
    }

    private update(): void {

        var bleHub: BleHub = new BleHub();
        bleHub.Name = 'Концентратор 1';
        this.Append(bleHub);

        //bleHub = new BleHub();
        //bleHub.Name = 'Концентратор 2';
        //this.Append(bleHub);

        //var bleHub: BleHub = new BleHub();
        //bleHub.Name = 'Концентратор 3';
        //this.Append(bleHub);
    }

    private showActions(): void {
        console.log(this);
        actions.innerHTML = '';
        actions.append(this.AddBleHubButton);
    }

    private AddBleHubButtonOnclick(): void {
        function reqListener(this: XMLHttpRequest, ev: ProgressEvent<EventTarget>) {
            interfaceZone.innerHTML = this.responseText;
        }

        var xhr: XMLHttpRequest = new XMLHttpRequest();
        xhr.onload = reqListener;
        xhr.open('get', '/BleHubs/Create', true);
        xhr.send();
        //xhr.setRequestHeader();
    }



}




