/// <reference path="TreeNode.ts" />

class Server extends TreeNode {

    constructor(
        parentContainer: HTMLUListElement
    ) {
        super();
        parentContainer.appendChild(this.Node);
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
