/*******************************************************************************
 * Copyright (c) 2010 by Timotei Dolean <timotei21@gmail.com>
 *
 * This program and the accompanying materials are made available
 * under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *******************************************************************************/
package org.wesnoth.utils;

import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;

import org.eclipse.core.resources.IFile;
import org.eclipse.core.resources.IResource;
import org.eclipse.ui.console.MessageConsole;
import org.wesnoth.Constants;
import org.wesnoth.Logger;
import org.wesnoth.preferences.Preferences;


public class GameUtils
{
	/**
	 * Runs campaign from the selected project
	 */
	public static void runCampaign()
	{
		Thread gameThread = new Thread(new Runnable() {
			@Override
			public void run()
			{
				runCampaignScenario(false);
			}
		});
		gameThread.start();
	}

	/**
	 * Runs a scenario from the selected file
	 */
	public static void runScenario()
	{
		Thread gameThread = new Thread(new Runnable() {
			@Override
			public void run()
			{
				runCampaignScenario(true);
			}
		});
		gameThread.start();
	}

	protected static void runCampaignScenario(boolean scenario)
	{
		if (WorkspaceUtils.getSelectedResource() == null)
		{
			GUIUtils.showWarnMessageBox("Please select a directory or a resource inside the " +
					"campaign project before.");
			return;
		}

		IResource selectedResource = WorkspaceUtils.getSelectedResource();

		try
		{
			String campaignId = null;
			String scenarioId = null;

			campaignId = ResourceUtils.getCampaignID(selectedResource);

			if (scenario == true && selectedResource instanceof IFile)
				scenarioId = ResourceUtils.getScenarioID((IFile)selectedResource);

			if (campaignId == null)
			{
				GUIUtils.showErrorMessageBox("You need to have a valid campaign file (_main.cfg)" +
						" in your directory or selected.");
				return;
			}

			if (scenario == true && scenarioId == null)
			{
				GUIUtils.showErrorMessageBox("I couldn't get the scenario's ID " +
						"or the file is not a scenario.");
				return;
			}

			List<String> args = new ArrayList<String>();
			args.add("-c");
			args.add(campaignId);
			if (scenario == true)
				args.add(scenarioId);
			startGame(args);
		} catch (Exception e)
		{
			Logger.getInstance().logException(e);
		}
	}

	/**
	 * Starts the game
	 */
	public static void startGame()
	{
		startGame(null);
	}

	/**
	 * Starts the wesnoth game with the specified extraArguments
	 * @param extraArgs Extra arguments given to the game, or null.
	 */
	public static void startGame(List<String> extraArgs)
	{
		List<String> args = new ArrayList<String>();
		String wesnothExec = Preferences.getString(Constants.P_WESNOTH_EXEC_PATH);
		String workingDir = Preferences.getString(Constants.P_WESNOTH_WORKING_DIR);
		if (wesnothExec.isEmpty() || workingDir.isEmpty())
		{
			GUIUtils.showErrorMessageBox("Please set the wesnoth's executable path first.");
			return;
		}

		if (extraArgs != null)
			args.addAll(extraArgs);

		// add the user's data directory path
		args.add("--config-dir");
		args.add(Preferences.getString(Constants.P_WESNOTH_USER_DIR));

		// we need to add the working dir (backward compatibility)
		args.add(workingDir);

		MessageConsole console = GUIUtils.createConsole("Wesnoth game:", null, true);
		ExternalToolInvoker.launchTool(wesnothExec, args,
				new OutputStream[] { console.newMessageStream() },
				new OutputStream[] { console.newMessageStream() });
	}

	/**
	 * Starts editor
	 */
	public static void startEditor()
	{
		startEditor("");
	}

	/**
	 * Starts the game editor on the specified file
	 * @param file The file to be edited
	 */
	public static void startEditor(IFile file)
	{
		if (file == null || !file.exists())
		{
			Logger.getInstance().log("non-existing map file",
					"Please select an existing map file before opening it.");
			return;
		}

		startEditor(file.getLocation().toOSString());
	}

	/**
	 * Starts the editor
	 * @param mapName
	 */
	public static void startEditor(String mapName)
	{
		startGame(getEditorLaunchArguments(mapName));
	}

	/**
	 * Gets a list of parameters for the game editor
	 * @param mapName the map to launch
	 * @return
	 */
	public static List<String> getEditorLaunchArguments(String mapName)
	{

		List<String> args = new ArrayList<String>(3);

		args.add("-e");
		if (mapName != null && !(mapName.isEmpty()))
			args.add(mapName);

		return args;
	}
}
