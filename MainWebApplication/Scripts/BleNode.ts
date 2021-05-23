
class BleNode extends HTMLLIElement {
    public BleServices: BleService[];
    constructor() {
        super();
        this.className = 'BleNode';
        this.addEventListener('click', this.OnClick);
    }

    private OnClick(): void {
        this.parentElement
            .querySelector(".nested")
            .classList.toggle("active");
        this.classList.toggle("caret-down");
    }
}
