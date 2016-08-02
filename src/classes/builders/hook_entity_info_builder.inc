<?php

class hook_entity_info_builder {
  protected $entityType;
  protected $fieldable;
  protected $toolboxInfo;
  protected $build;

  public function __construct($entityType = NULL, $fieldable = NULL) {
	if (!empty($entityType)) {
	  throw new MissingEntityTypeException(array('class' => self::class));
	}
	$this->entityType  = $entityType;
	$this->toolboxInfo = entity_toolbox_entity_get_info($this->entityType);
  }

  public function build() {
	$toolboxInfoController = new ToolboxInfoController($this->entityType, $this->toolboxInfo);
	$build                 = array(
	  'label'             => $toolboxInfoController->label(),
	  'plural label'      => $toolboxInfoController->labelPlural(),
	  'entity class'      => $toolboxInfoController->entityClass(),
	  'controller class'  => $toolboxInfoController->controllerClass(),
	  'base table'        => $toolboxInfoController->baseTable(),
	  'fieldable'         => $toolboxInfoController->isFieldable(),
	  'entity keys'       => $toolboxInfoController->keys(),
	  'creation callback' => $toolboxInfoController->createCallback(),
	  'access callback'   => $toolboxInfoController->accessCallback(),
	  'label callback'    => $toolboxInfoController->labelCallback(),
	  'uri callback'      => $toolboxInfoController->uriCallback(),
	  'module'            => $toolboxInfoController->module(),
	  'admin ui'          => array(
		'path'             => entity_admin_path($this->entityType),
		'file'             => "",
		'controller class' => "",
	  ),
	);
	$this->build           = $build;
  }
}