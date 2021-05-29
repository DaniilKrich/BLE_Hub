
class BleService extends TreeNode{
    constructor() {
        super();
        this.Update = this.update;
    }

    private update(): void {
        var bleCharaceristic: BleCharaceristic = new BleCharaceristic();
        bleCharaceristic.Name = 'Температура';
        this.Append(bleCharaceristic);

        bleCharaceristic = new BleCharaceristic();
        bleCharaceristic.Name = 'Влажность';
        this.Append(bleCharaceristic);
    }
}
