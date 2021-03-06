  ! -*- mode: f90; -*-
  ! Body of all the specific procedures of generic interface "read_column".
  
  call new_unit(unit)
  open(unit, file=file, status='old', action='read', position='rewind')

  ! Fill non-optional arguments: first and last line which will
  ! actually be read, taking information from the file itself if
  ! necessary.
  
  first_not_opt = opt_merge(first, 1)
  last_not_opt = opt_merge(last, 0)

  if (last_not_opt == 0) then
     call count_lines(unit, last_not_opt)

     if (last_not_opt == 0) then
        print *, 'Empty file.'
        stop 1
     end if
     
     rewind(unit)
  end if

  ! Go to first line to read:
  do i = 1, first_not_opt - 1
     read(unit, fmt=*)
  end do
  
  allocate(a(last_not_opt - first_not_opt + 1))
  read(unit, fmt=*) a
  close(unit)
