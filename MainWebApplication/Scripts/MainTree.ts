class MainTree  {
    private tree: HTMLUListElement;

    constructor(
        private root: HTMLDivElement) {
       



        //this.addEventListener("click", (e) => {
        //    if (e.target == null)
        //        return;
        //    var el = e.target as HTMLLIElement

        //    if (el.className == 'Characteristic') {

        //        var xhr: XMLHttpRequest = new XMLHttpRequest();
        //        xhr.onload = reqListener;
        //        xhr.open("get", "yourFile.txt", true);
        //        xhr.send();

        //        //xhr.setRequestHeader();


        //        actions.innerHTML = el.getAttribute('data');
        //    }
            //if (el.className == 'Hub') {
            //    actions.innerHTML = el.getAttribute('data');
            //}
            //if (el.className == 'BleSensor') {
            //    actions.innerHTML = el.getAttribute('data');
            //}
        //});





        this.Update();
    }




    public Update(): void {
        this.root.innerHTML = '';
        this.tree = <HTMLUListElement>document.createElement('ul');
        this.tree.id = 'Tree';
        this.root.appendChild(this.tree);



        /*this.BleHubs = new*/ 

        //var list: HTMLLIElement = new HTMLLIElement();

        /*
          <span class="caret caret-down">Сервер</span>
            <ul class="nested active">
         */

        var server = new Server(this.tree);
        server.Name = 'Сервер';


        var xhr: XMLHttpRequest = new XMLHttpRequest();

        xhr.onload = this.FillBleHubs;
        xhr.open("get", "/Home/GetBleHubs", true);
        xhr.send();

        //xhr.setRequestHeader();


        //actions.innerHTML = el.getAttribute('data');

    }

    private FillBleHubs(): void {
        var msg: string = 'ok!';
        alert(msg);
    }



}
