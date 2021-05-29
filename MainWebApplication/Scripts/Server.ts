/// <reference path="TreeRoot.ts" />

class Server extends TreeRoot {

    constructor(
        parentContainer: HTMLElement
    ) {
        super(parentContainer);
        this.Update = this.update;
    }

    private update(): void {
        var bleHub: BleHub = new BleHub();
        bleHub.Name = 'Концентратор 1';
        this.Append(bleHub);

        bleHub = new BleHub();
        bleHub.Name = 'Концентратор 2';
        this.Append(bleHub);

        var bleHub: BleHub = new BleHub();
        bleHub.Name = 'Концентратор 3';
        this.Append(bleHub);
    }


}
