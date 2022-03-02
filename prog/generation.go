// Copyright 2021, Developed by Tsinghua Wingtecher Lab and Shumuyulin Ltd, All rights reserved.
// Copyright 2015 syzkaller project authors. All rights reserved.
// Use of this source code is governed by Apache 2 LICENSE that can be found in the LICENSE file.

package prog

import (
	"math/rand"
)

// Generate generates a random program with ncalls calls.
// ct contains a set of allowed syscalls, if nil all syscalls are used.
func (target *Target) Generate(rs rand.Source, ncalls int, ct *ChoiceTable) *Prog {
	p := &Prog{
		Target: target,
	}
	r := newRand(target, rs)
	s := newState(target, ct, nil)
	for len(p.Calls) < ncalls {
		calls := r.generateCall(s, p, len(p.Calls))
		for _, c := range calls {
			s.analyze(c)
			p.Calls = append(p.Calls, c)
		}
	}
	// For the last generated call we could get additional calls that create
	// resources and overflow ncalls. Remove some of these calls.
	// The resources in the last call will be replaced with the default values,
	// which is exactly what we want.
	for len(p.Calls) > ncalls {
		p.removeCall(ncalls - 1)
	}
	p.sanitizeFix()
	p.debugValidate()
	return p
}
 
func initMap(mmp map[string]int) map[string]int {
	mmp = make(map[string]int)
	mmp["open"] = 1
	mmp["close"] = -1
	mmp["mount"] = 2
	mmp["unmount"] = -2
	return mmp
}

func CheckMatch(callName string, mmp map[string]int) int {
	if v, ok := mmp[callName]; ok {
		if v > 0 {
			return 1
		} else {
			return -1
		}
	} else {
		return 0
	}
}

func locateSyscall(idx int, mmp map[string]int) string {
	re := -idx
	for s, val := range mmp {
		if val == re {
			return s
		}
	}
	return ""
}

func TaskStateUpdate(task []*Prog, ncalls int, r *randGen, s *state) []*Prog {
	CheckMatchNum := 0
	var callToidx map[string]int
	callToidx = initMap(callToidx)
	for _, prog := range task {
		for _, call := range prog.Calls {
			isExist := CheckMatch(call.Meta.CallName, callToidx)
			if isExist == 1 {
				CheckMatchNum = CheckMatchNum | (1 << callToidx[call.Meta.CallName])
			}
			if isExist == -1 {
				CheckMatchNum = CheckMatchNum ^ (1 << (-callToidx[call.Meta.CallName]))
			}
		}

		tmp := CheckMatchNum
		lenth := 0
		for true {
			if 0 == tmp {
				break
			}
			tmp >>= 1
			lenth++
		}

		for i := 0; i < lenth; i++ {
			if tmp&(1<<i) == 1 && len(prog.Calls) < ncalls {
				CallName := locateSyscall(i, callToidx)
				call := r.TaskgenerateParticularCall(s, CallName)
				prog.Calls = append(prog.Calls, call)
			}
		}
	}
	return task
}

func (target *Target) TaskGenerate(rs rand.Source, ncalls int, ct *ChoiceTable) []*Prog {
	rand := rand.New(rs)
	taskLen := rand.Intn(7) + 1
	tasks := make([]*Prog, 0, taskLen)

	for i := 0; i < taskLen; i++ {
		p := &Prog{
			Target: target,
			Prio:   rand.Intn(100),
		}
		r := newRand(target, rs)
		s := newState(target, ct, nil)

		for len(p.Calls) < ncalls {
			calls := r.generateCall(s, p, len(p.Calls))
			for _, c := range calls {
				s.analyze(c)
				p.Calls = append(p.Calls, c)
			}

		}
		// For the last generated call we could get additional calls that create
		// resources and overflow ncalls. Remove some of these calls.
		// The resources in the last call will be replaced with the default values,
		// which is exactly what we want.
		for len(p.Calls) > ncalls {
			p.removeCall(ncalls - 1)
		}
		p.sanitizeFix()
		p.debugValidate()
		tasks = append(tasks, p)
	}
	r := newRand(target, rs)
	s := newState(target, ct, nil)
	tasks = TaskStateUpdate(tasks, taskLen, r, s)
	return tasks
}
