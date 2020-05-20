These were tested using Linux Mint, but probably any Debian-based distro
would be similar.

Need to uncomment these in /etc/bash.bashrc and open a new shell:

# enable bash completion in interactive shells
#if [ -f /etc/bash_completion ]; then
#    . /etc/bash_completion
#fi

Newer distros may have a slightly different syntax than above, but it works.
To simply enable completion in the current shell, just type this below (which
is what the above is doing in the bashrc)

  . /etc/bash_completion

The file usually contains something like this:

  . /usr/share/bash-completion/bash_completion

Which is where the whole machinery does the magic.


For custom completions (e.g. tablen, dumpit), put the files in:
  
  /etc/bash_completion.d/

Give them 644 permissions and start a new shell. Typing:

  tablen --

and hitting the tab key will cycle (if that is enabled), otherwise, typing

  tablen --co

should complete to --color.

To see all completions available in the current shell, type:

  complete -p


Sample completion file for tablen:
===============================================================================
_tablen()
{
  local cur prev opts
  COMPREPLY=()
  cur="${COMP_WORDS[COMP_CWORD]}"
  prev="${COMP_WORDS[COMP_CWORD-1]}"
  opts="--all --color --filename --help --longlines --tabs --verbose --version"

    # to complete long options
  if [[ ${cur} == -* ]] ; then
    COMPREPLY=( $(compgen -W "${opts}" -- ${cur}) )
    return 0
  fi

    # to complete filenames
  COMPREPLY=( $(compgen -f ${cur}) )
}
complete -F _tablen tablen
===============================================================================


I got most of the information from here:
https://debian-administration.org/article/316/An_introduction_to_bash_completion_part_1
https://debian-administration.org/article/317/An_introduction_to_bash_completion_part_2
