function update_files
{
    current_dir=$1
    
    cp $TAMPLATE_FILE/*.sh $current_dir
    cp $TAMPLATE_FILE/func_tests/scripts/*.sh $current_dir/func_tests/scripts/
    
}

TAMPLATE_FILE=/Users/dmitriy/BMSTU/sem_2/C/lab_works/dir_template


# echo -n "n: Numbers | s: String\nType of comparator: "
# read type_comparator
# if [ $type_comparator = "s" ]; then
#     read sub_string
# fi

if [ -e "$1" ]; then
    cd $1
else
    return 1;
fi

for lab_number in $(ls | grep -E "lab_[0-9]+")
do
    cd $lab_number
    for task in $(ls)
    do
        cd $task

        # pwd
        update_files $(pwd)

        cd ..
    done 
    cd ..
done

# update_files /Users/dmitriy/BMSTU/sem_2/C/lab_works/123
