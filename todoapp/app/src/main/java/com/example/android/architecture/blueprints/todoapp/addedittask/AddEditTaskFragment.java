/*
 * Copyright 2016, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.example.android.architecture.blueprints.todoapp.addedittask;

import android.app.Activity;
import android.os.Bundle;
import android.text.Editable;
import android.text.TextWatcher;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

import com.example.android.architecture.blueprints.todoapp.R;
import com.google.android.material.floatingactionbutton.FloatingActionButton;
import com.google.android.material.snackbar.Snackbar;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.fragment.app.Fragment;

import static com.google.common.base.Preconditions.checkNotNull;

/**
 * Main UI for the add task screen. Users can enter a task title and description.
 */
public class AddEditTaskFragment extends Fragment implements AddEditTaskContract.View {

    public static final String ARGUMENT_EDIT_TASK_ID = "EDIT_TASK_ID";

    private AddEditTaskContract.Presenter mPresenter;

    private TextView mTitle;

    private TextView mDescription;

    public static AddEditTaskFragment newInstance() {
        return new AddEditTaskFragment();
    }

    public AddEditTaskFragment() {
        // Required empty public constructor
    }

    @Override
    public void onResume() {
        super.onResume();
        mPresenter.start();
    }

    @Override
    public void setPresenter(@NonNull AddEditTaskContract.Presenter presenter) {
        mPresenter = checkNotNull(presenter);
    }

    @Override
    public void onActivityCreated(Bundle savedInstanceState) {
        super.onActivityCreated(savedInstanceState);

        FloatingActionButton fab =
                (FloatingActionButton) getActivity().findViewById(R.id.fab_edit_task_done);
        fab.setImageResource(R.drawable.ic_done);
        fab.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                mPresenter.saveTask(mTitle.getText().toString(), mDescription.getText().toString());
            }
        });

        mDescription.addTextChangedListener(new TextWatcher() {
            @Override
            public void afterTextChanged(Editable s) {}
            @Override
            public void beforeTextChanged(CharSequence s, int start,
                                          int count, int after) {
            }
            @Override
            public void onTextChanged(CharSequence s, int start,
                                      int before, int count) {
                //메모 내용이 변할 때마다 호출되는 함수. (타이핑이나 붙여넣기 기능에서도 동작함)
                //TODO : 4-1) 7Segment - 현재 작성중인 글자 수를 보여주는 함수 호출 (data: mDescription.getText().toString().length())
            }
        });
    }

    @Override
    public void onStop() {
        //작성화면에서 나갈 때 호출되는 함수로, 글자수 초기화가 이루어져야 한다.
        //TODO : 4-2) 7Segment - 현재 작성중인 글자 수를 보여주는 함수 호출 (data: 0)
        super.onStop();
    }

    @Nullable
    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View root = inflater.inflate(R.layout.addtask_frag, container, false);
        mTitle = (TextView) root.findViewById(R.id.add_task_title);
        mDescription = (TextView) root.findViewById(R.id.add_task_description);
        setHasOptionsMenu(true);
        return root;
    }

    @Override
    public void showEmptyTaskError() {
        Snackbar.make(mTitle, getString(R.string.empty_task_message), Snackbar.LENGTH_LONG).show();
    }

    @Override
    public void showTasksList() {
        getActivity().setResult(Activity.RESULT_OK);
        getActivity().finish();
    }

    @Override
    public void setTitle(String title) {
        mTitle.setText(title);
    }

    @Override
    public void setDescription(String description) {
        mDescription.setText(description);
    }

    @Override
    public boolean isActive() {
        return isAdded();
    }
}
