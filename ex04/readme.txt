name: Athena Grigoraki
AM: csd4109

Το slack time ειναι το deadline της διεργασιας - τον τωρινο χρονο - εναπομειναντα χρονο για εκτελεση
της διεργασιας (computation - elapsed). Οταν εχει ληξει η διορια μιας διεργασιας(slack <= 0 η εχει ληξει το deadline) κανω ελεγχο για να μην την εκτελεσω κανοντας
deactivate_task και η διεργασια βγαινει απο την ουρα. Επειτα υπολογιζω το slack time των υπολοιπων διεργασιων μεχρι να βρω αυτη με το minimum slack time
για να εκτελεστει.Στο demo προγραμμα που εφτιαξα, εκανα να παιρνει απο command line arguement ορισμα x τις child processes διαφορετικα σαν default παιρνει το 2. 
Η διαδικασια γονεας καλει την set deadlines με ορισματα deadline(100 + gettimeofday) και computation time = i.Στο μεταξυ καθε child process κανει sleep.
Το gettimeofday ειναι για user space ενω το do_gettimeofday για kernel space. Το curr αφορα την τρεχουσα διαδικασια στον CPU.(rq->curr).
Τρεχοντας το demo για καποιο λογο ενω υπολογιζει το current time, στα πεδια deadline και computation time του task struct δεν τα βρισκει και μπαινει η τιμη 0.
Επομενως ολες οι διαδικασιες γινονται deactivate και βγαζει ενα ακαταλαβιστικο αποτελεσμα. Εγραψα εναν κωδικα που θεωρω ειναι σωστος μεσα στο sched.c που περιγραφει 
αυτο που χρειαζεται απλα δεν δουλευει σωστα λογω του παραπανω λογου.
 
 
 
