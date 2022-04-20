window.indexedDB = window.indexedDB || window.mozIndexedDB || 
         window.webkitIndexedDB || window.msIndexedDB;
         
         //prefixes of window.IDB objects
         window.IDBTransaction = window.IDBTransaction || 
         window.webkitIDBTransaction || window.msIDBTransaction;
         window.IDBKeyRange = window.IDBKeyRange || window.webkitIDBKeyRange || 
         window.msIDBKeyRange;

if(!window.indexedDb)
{
	alert("Browser doesn't support indexedDB");
}

var db=null;
var request=window.indexedDB.open("Shop",1);
request.onerror=function(event){
	console.log("Error");
};
request.onsuccess=function(event){
	db=request.result;
	console.log("success: "+db);
};
request.onupgradeneeded=function(event){
	db=event.target.result;
	var objectStore=createObjectStore("Items", {keypath: ['name','manufacturer']});
	objectStore.createIndex("price", "price", {unique : false});
};

function add()
{
	var na=document.getElementById("name").value;
	var mf=document.getElementById("mfr").value;
	var pr=document.getElementById("price").value;
	var item={
			  name:document.getElementById("name").value,
			  manufacturer:document.getElementById("mfr").value, 
			  price:document.getElementById("price").value
			};
	console.log(item);
	var req=db.transaction(['Items'], 'readwrite')
			.objectStore('Items')
			.add(item);
	req.onsuccess=function(event){
		console.log("Written successfully");
	};
	req.onerror=function(event){
		console.log("Error adding data");
	};
}