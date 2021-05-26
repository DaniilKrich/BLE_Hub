class TreeNode {
    protected parent: TreeNode;
    protected children: TreeNode[] = [];
    protected container: HTMLUListElement =
        <HTMLUListElement>document.createElement('ul');

    protected title: HTMLSpanElement =
        <HTMLSpanElement>document.createElement('span');

    private nodeWrapper: HTMLLIElement = <HTMLLIElement>document.createElement('li');

    /** li element to insert into parent ul*/
    public get Node(): HTMLLIElement {
        return this.nodeWrapper;
    }

    constructor(
    ) {
        // <span class="caret caret-down" > Сервер < /span>
        this.title = <HTMLSpanElement>document.createElement('span');
        this.title.className = 'caret';
        this.title.addEventListener('click', this.OnClick);
        this.nodeWrapper.appendChild(this.title);

        // <ul class="nested active" >
        this.container.className = 'nested';
        this.nodeWrapper.appendChild(this.container);



    }

    public set Name(name: string) {
        if (this.IsNullOrWhiteSpace(this.title.textContent)) {
            if (this.Update)
                this.Update();
        }
        else {
            if (this.Rename)
                this.Rename();
        }
        this.title.textContent = name;
    }

    public get Name(): string {
        return this.title.textContent;
    }

    public Append(node: TreeNode): void {
        node.parent = this;
        this.children.push(node);
        this.container.appendChild(node.Node);

    }

    private IsNullOrWhiteSpace(str: string): boolean {
        return str === null || str.match(/^\s*$/) !== null;
    }

    private OnClick(this: HTMLSpanElement, ev: MouseEvent): void {
        this.parentElement
            .querySelector(".nested")
            .classList.toggle("active");

        this.classList.toggle("caret-down");
    }

    public Update: Function;
    public Rename: Function;

}