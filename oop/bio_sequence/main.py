import seq

dna = seq.SeqDNA()
dna.load_from('fasta/example/seq.fas')

rna = dna.transcribe()

seqaaframes = rna.translate()

seqaaframes.save_as('fasta/seq.aa.fas')

dna.load_from('fasta/example/mult_seq.fas', -1)
dna.transcribe().translate().save_as('fasta/mult_seq.aa_last.fas')

dnas = dna.load_from('fasta/example/mult_seq.fas')

for _dna in dnas:
    _dna.transcribe().translate().save_as(f'fasta/mult_seq.aa_{_dna.id}.fas')
