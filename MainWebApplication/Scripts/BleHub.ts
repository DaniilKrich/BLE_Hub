
class BleHub extends HTMLLIElement {
    public BleNodes: BleNode[];

    constructor() {
        super();

         //<span class="caret hub caret-down">Концентратор 1</span>
        var name: HTMLSpanElement = new HTMLSpanElement();
        name.className = 'caret';
        name.textContent = 'Концентратор 1';
        this.appendChild(name);

        // <ul class="nested active">
        var nodes: HTMLUListElement = new HTMLUListElement();
        nodes.className = 'nested';
        this.appendChild(nodes);


    }

    public GetScan() {

    }

    public GetNode() {

    }
}
