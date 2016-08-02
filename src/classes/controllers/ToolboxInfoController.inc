<?php

class ToolboxInfoController {
  protected $entityType;
  protected $toolboxInfo;
  protected $toolboxVersion;

  public function __construct($entityType = NULL, $toolboxInfo = array()) {
	if (!isset($entityType)) {
	  throw new MissingEntityTypeException(array('class' => self::class));
	}
	$this->entityType = $entityType;
	if (empty($toolboxInfo)) {
	  throw new ToolboxInfoNotProvidedException();
	}
	$this->toolboxInfo = $toolboxInfo;
  }

  public function entityType() {
	return $this->entityType;
  }

  public function module() {
  }

  public function baseTable() {
  }

  public function revisionTable() {
  }

  public function relationTables() {
  }

  public function callbacks() {
  }

  public function createCallback() {
  }

  public function labelCallback() {
  }

  public function accessCallback() {
  }

  public function titleCallback() {
  }

  public function viewCallback() {
  }

  public function classes() {
  }

  public function paths() {
  }

  public function isFieldable() {
  }

  public function isExportable() {
  }

  public function hasTranslations() {
  }

  public function hasRevisions() {
  }

  public function keys() {
  }

  public function entityGroup() {
  }

  public function childrenInherit() {
  }

}