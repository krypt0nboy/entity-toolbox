<?php

/**
 * Created by PhpStorm.
 * User: ddoucoure
 * Date: 10/08/16
 * Time: 11:29
 */
class PermissionBuilderEntityToolboxDependent extends EntityToolboxDependentHookBuilder {

  protected $entityBundle = array();

  public function __construct(array $args = array()) {
    $this->mergeConstructArgs(
      array(
        'hook' => 'permission'
      ),
      $args
    );
    parent::__construct($args);

    $info = entity_get_info($this->entityType);
    if (!empty($info['bundles'])) {
      foreach ($info['bundles'] as $key => $bundle) {
        $this->entityBundle[$key] = (!empty($bundle['label'])) ? $bundle['label'] : $key;
      }
    }
    else {
      $this->entityBundle = (!empty($info['label'])) ? array($this->entityType => $info['label']) : array($this->entityType => $this->entityType);
    }
  }

  public function build() {
    $adminPermission  = $this->buildAdministerPermission();
    $addPermission    = $this->buildAddPermission();
    $editPermission   = $this->buildEditPermission();
    $deletePermission = $this->buildDeletePermission();
    $viewPermission   = $this->buildViewPermission();
    $this->build      = array_merge($adminPermission, $addPermission, $editPermission, $deletePermission, $viewPermission);

    return $this->build;
  }

  public function buildAdministerPermission() {
    return array(
      "administer $this->entityType" => array(
        'title'       => t(''),
        'description' => t('Perform administration task for @entity', array('@entity' => $this->entityType)),
      ),
    );
  }

  /**
   * Build Add Permission operation by bundle
   *
   * @return array
   */
  public function buildAddPermission() {
    $addPermission = array();

    foreach ($this->entityBundle as $bundle => $label) {
      $addPermission["create new $bundle $this->entityType"] = array(
        'title' => t('@label: Create new @bundle @entity', array(
          '@label'  => $label,
          '@bundle' => $bundle,
          '@entity' => $this->entityType
        ))
      );
    }

    return $addPermission;
  }

  /**
   * Build Edit Permission operation by bundle
   *
   * @return array
   */
  public function buildEditPermission() {
    $editPermission = array();

    foreach ($this->entityBundle as $bundle => $label) {
      $editPermission["edit any $bundle $this->entityType"] = array(
        'title' => t('@label: Edit any @bundle @entity', array(
          '@label'  => $label,
          '@bundle' => $bundle,
          '@entity' => $this->entityType
        ))
      );
      $editPermission["edit own $bundle $this->entityType"] = array(
        'title' => t('@label: Edit own @bundle @entity', array(
          '@label'  => $label,
          '@bundle' => $bundle,
          '@entity' => $this->entityType
        ))
      );
    }

    return $editPermission;
  }

  /**
   * Build Delete Permission operation by bundle
   *
   * @return array
   */
  public function buildDeletePermission() {
    $deletPermission = array();

    foreach ($this->entityBundle as $bundle => $label) {
      $deletPermission["delete any $bundle $this->entityType"] = array(
        'title' => t('@label: Delete any @bundle @entity', array(
          '@label'  => $label,
          '@bundle' => $bundle,
          '@entity' => $this->entityType
        ))
      );
      $deletPermission["delete own $bundle $this->entityType"] = array(
        'title' => t('@label: Delete any @bundle @entity', array(
          '@label'  => $label,
          '@bundle' => $bundle,
          '@entity' => $this->entityType
        ))
      );
    }

    return $deletPermission;
  }

  /**
   * Build View Permission operation by bundle
   *
   * @return array
   */
  public function buildViewPermission() {
    $viewPermission = array();

    foreach ($this->entityBundle as $bundle => $label) {
      $viewPermission["view $bundle $this->entityType"] = array(
        'title' => t('@label: View @bundle $entity', array(
          '@label'  => $label,
          '@bundle' => $bundle,
          '@entity' => $this->entityType
        ))
      );
    }

    return $viewPermission;
  }

}