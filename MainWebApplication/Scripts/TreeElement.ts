class TreeElement {
    public parent?: TreeElement;
    protected children?: TreeElement[];
    protected container?: HTMLUListElement;
    protected title: HTMLSpanElement = document.createElement('span') as HTMLSpanElement;

    protected nodeWrapper: HTMLElement;

    /** li element to insert into parent ul*/
    public get Node(): HTMLElement {
        return this.nodeWrapper;
    }

    constructor() {
        // <span class="caret caret-down" > Сервер < /span>
        //this.title = <HTMLSpanElement>document.createElement('span');
        this.title.classList.add('Clickable');
    }

    public set ID(id: number) {
        this.title.attributes['dbid'] = id;
    }
    public get ID(): number {
        return this.title.attributes['dbid'];
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


    private IsNullOrWhiteSpace(str: string): boolean {
        return str === null || str.match(/^\s*$/) !== null;
    }

    protected set OnClick(f: (this: HTMLSpanElement, ev: MouseEvent) => void) {
        this.title.addEventListener('click', f);
    }

    public Update: Function;
    public Rename: Function;
}