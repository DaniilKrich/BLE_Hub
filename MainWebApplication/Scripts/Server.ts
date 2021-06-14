/// <reference path="TreeRoot.ts" />

class Server extends TreeRoot {
    private AddBleHubButton: HTMLDivElement;


    constructor(
        parentContainer: HTMLElement
    ) {
        super(parentContainer);

        this.Update = this.update;

       
        this.OnClick = this.onClick;

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

    private onClick(): void {
        console.log(this);
        actions.innerHTML = '';
        this.AddBleHubButton = document.createElement('div') as HTMLDivElement;
        this.AddBleHubButton.className = 'Action';
        this.AddBleHubButton.innerText = 'Добавление концентратора';
        this.AddBleHubButton.onclick = this.AddBleHubButtonOnclick;
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




