

class MainTree extends HTMLUListElement {
    public BleHubs: BleHub[];

    constructor() {
        super();// = new HTMLUListElement();
        this.id="Root"




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
        /*this.BleHubs = new*/ 

        //var list: HTMLLIElement = new HTMLLIElement();

        /*
          <span class="caret caret-down">Сервер</span>
            <ul class="nested active">
         */
        this.innerHTML = '';

        var server = new Server();
        this.appendChild(server);



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
