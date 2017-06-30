function removeAllOldSamples(collection,sampleNumber)
{
	var sampleInitiate=collection.charAt(0);
	for ( j = 1; j < sampleNumber+1; ++j ) {
            samplename=sampleInitiate+j;
	    db[samplename].drop();
						}
}





function SamplingWithoutReplacement(snumber,dnumber,cname) {
	DBQuery.shellBatchSize = snumber*100;
	var sampleInitiate=cname.charAt(0);
	for ( j = 1; j < snumber+1; ++j ) {
            var remain=0;
            var before = new Date()
	    samplename=sampleInitiate+j;
	    print(samplename + " started");

	    var c=db[samplename].count();
            if(c==dnumber)continue;
            else{
            remain=dnumber-c;
            db[cname].aggregate([{$sample:{size: remain}}]).forEach(function(doc){ db[samplename].insert(doc);});
	    print("doc count in " +samplename+" is: "+db[samplename].count());
                       }
var after = new Date()
execution_mills = after - before
print("Mills: "+execution_mills);
}
}




function creatIndexforSamples(coll,sampleNumber){
switch(coll) {
    case 'social':
        db[coll].createIndex({email:1});
	var sampleInitiate=coll.charAt(0);
        for ( j = 1; j < sampleNumber+1; ++j ) {
            samplename=sampleInitiate+j;
	    db[samplename].createIndex({email:1});
						}
        break;
    case 'phone':
        db[coll].createIndex({email:1});
        db[coll].createIndex({phone:1});
	var sampleInitiate=coll.charAt(0);
        for ( j = 1; j < sampleNumber+1; ++j ) {
            samplename=sampleInitiate+j;
	    db[samplename].createIndex({email:1});
	    db[samplename].createIndex({phone:1});
						}
        break;
    case 'health':
        db[coll].createIndex({ssn:1});
        db[coll].createIndex({phone:1});
	var sampleInitiate=coll.charAt(0);
        for ( j = 1; j < sampleNumber+1; ++j ) {
            samplename=sampleInitiate+j;
	    db[samplename].createIndex({ssn:1});
	    db[samplename].createIndex({phone:1});
						}
        break;
    case 'finance':
        db[coll].createIndex({ssn:1});
	var sampleInitiate=coll.charAt(0);
        for ( j = 1; j < sampleNumber+1; ++j ) {
            samplename=sampleInitiate+j;
	    db[samplename].createIndex({ssn:1});
						}
        break;
    default:
        print("Error");
}
}



function CrossCorrelationAnalysis(source,destination,numberOfSamples,localfield, foreignfield) {
         var correlation     = [];
         var sourceInit      = source.charAt(0);
	 var destinationInit = destination.charAt(0);
	 for ( j = 1; j < numberOfSamples+1; ++j ) {

	    samplename       = sourceInit+j;
            resCollection   = samplename+destinationInit;
            db[resCollection].drop();
            //print("Number of documents in "+samplename+ " is: " + db[samplename].count());
            var before       = new Date()	    
db[samplename].aggregate([{$lookup:{from:destination,localField:localfield,foreignField:foreignfield,as:"corr" }},{$match:{"corr":{$ne:[]}}},{ $out : resCollection }]);

            var after = new Date()
            correlation[j]=db[resCollection].count();
	    execution_mills = after - before
            //print("Mills: "+execution_mills);
						}
	   var sum=0;
	   for ( j = 1; j < numberOfSamples+1; ++j ) {	   
 print("correlation["+j+"] is "+ correlation[j]);
	   sum=sum+correlation[j];                     
                                                      }
	  var ave=(sum/numberOfSamples);
          var percent=(ave/db[samplename].count())*100;		
print("===============["+source+"-->"+destination+"]==================================");
print("Average: "+ ave+ " Percent: "+percent);
print("======================================================================");
}


function samplesCCAnalysis(source,destination,numberOfSamples,localfield, foreignfield) {
var correlation     = [];
var sourceInit      = source.charAt(0);
var destinationInit = destination.charAt(0);
for ( j = 1; j < numberOfSamples+1; ++j ) {
    sourceSamplename            = sourceInit+j;
    destinationSampleName       = destinationInit+j;
    resCollection   = "CC"+sourceSamplename+destinationSampleName;
    db[resCollection].drop();
    print("Number of documents in "+sourceSamplename+ " is :" + db[sourceSamplename].count() +" and "+ destinationSampleName+ " is :"+ db[destinationSampleName].count());
    db[sourceSamplename].aggregate([{$lookup:{from:destinationSampleName,localField:localfield,foreignField:foreignfield,as:"corr" }},{$match:{"corr":{$ne:[]}}},{ $out : resCollection }]);
    correlation[j]=db[resCollection].count();
					}
var av=0.0;
for ( j = 1; j < numberOfSamples+1; ++j ) {
    sourceSamplename            = sourceInit+j;
    destinationSampleName       = destinationInit+j;
    av=av+ correlation[j];
    print("correlation "+ sourceSamplename + "["+j+"]"+ " --> " + destinationSampleName + "["+j+"] : " + correlation[j]);
    db[resCollection].drop();
                                         }
print("================================");
print("Average: "+av/numberOfSamples);
print("================================");
}


//====================================================================================================================================

removeAllOldSamples('phone',50);
removeAllOldSamples('social',50);
removeAllOldSamples('health',50);
removeAllOldSamples('finance',50);

SamplingWithoutReplacement(50,10000,'social');
SamplingWithoutReplacement(50,10000,'phone');
SamplingWithoutReplacement(50,10000,'health');
SamplingWithoutReplacement(50,10000,'finance');

creatIndexforSamples('social',50);
creatIndexforSamples('phone',50);
creatIndexforSamples('health',50);
creatIndexforSamples('finance',50);

CrossCorrelationAnalysis('health','phone',50,'phone','phone'); 
CrossCorrelationAnalysis('health','finance',50,'ssn','ssn');
CrossCorrelationAnalysis('social','phone',50,'email','email');

samplesCCAnalysis("social","phone",50,"email", "email");
samplesCCAnalysis("phone","health",50,"phone", "phone");
samplesCCAnalysis("health","finance",50,"ssn", "ssn");



db.health.aggregate([{$lookup:{from:"finance",localField:"ssn",foreignField:"ssn",as:"corr" }},{$match:{"corr":{$ne:[]}}},{ $out : "healthFinance" }]);
db.social.aggregate([{$lookup:{from:"phone",localField:"email",foreignField:"email",as:"corr" }},{$match:{"corr":{$ne:[]}}},{ $out : "socialPhone" }]);
db.phone.aggregate([{$lookup:{from:"health",localField:"phone",foreignField:"phone",as:"corr" }},{$match:{"corr":{$ne:[]}}},{ $out : "phoneHealth" }]);

