function update_files
{
    
}

cd /Users/dmitriy/BMSTU/sem_2/C/lab_works/
for lab_number in $(ls | grep -E "lab_[0-9]+")
do
    cd $lab_number
    for task in $(ls)
    do
        cd $task

        pwd

        cd ..
    done 
    cd ..
done