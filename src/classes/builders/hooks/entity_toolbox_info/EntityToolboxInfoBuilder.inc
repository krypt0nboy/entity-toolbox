<?php

/**
 * Class EntityToolboxInfoBuilder
 *
 * Base build class for hook_entity_toolbox_info().
 */
class EntityToolboxInfoBuilder extends EntityDependentHookBuilder {

  /**
   * @var array $rawData
   */
  protected $rawData = array();

  /**
   * @var array $groupInfo
   */
  protected $groupInfo = array();

  /** {{@inheritdoc}} */
  public function __construct(array $args = array()) {
    $args = $this->mergeConstructArgs(array(
      'hook'                 => 'entity_toolbox_info',
      'self_extract_marker'  => '',
      'self_replace_marker'  => 'toolbox_info_',
      'key_builders_classes' => array(
        'labels'    => 'EntityToolboxInfoLabelsBuilder',
        'tables'    => 'EntityToolboxInfoTablesBuilder',
        'callbacks' => 'EntityToolboxInfoCallbacksBuilder',
        'keys'      => 'EntityToolboxInfoKeysBuilder',
      )
    ),
      $args
    );
    parent::__construct($args);
  }

  /**
   *
   */
  protected function initTemplateVars() {
    $toolboxTemplateVars = $this->extractTemplateVars($this->rawData, $this->selfExtractMarker, $this->selfReplaceMarker);
    $this->setTemplateVars($toolboxTemplateVars);
    $this->updateTemplateVars('toolbox_info_entity_type', $this->entityType);
    $this->updateTemplateVars('toolbox_info_module_path', drupal_get_path('module', $this->rawData['module']));
  }

  /**
   * @param string $key
   * @return array
   */
  public function getRawData($key = NULL) {
    return isset($key) ? $this->rawData[$key] : $this->rawData;
  }

  /**
   * @param array $rawData
   */
  public function setRawData($rawData) {
    $this->rawData = $rawData;
    if (isset($this->rawData['group'])) {
      $this->setGroupInfo(entity_toolbox_entity_group_get_info($this->rawData['group']));
    }
  }

  public function getRawProperties($property = NULL) {
    if (!empty($this->rawData['properties'])) {
      return isset($property) ? !empty($this->rawData['properties'][$property]) ? $this->rawData['properties'][$property] : array() : $this->rawData['properties'];
    }
    else {
      return array();
    }
  }

  /**
   *
   */
  protected function postSetRawData() {
    if (isset($rawData['group'])) {
      $this->setGroupInfo(entity_toolbox_entity_group_get_info($rawData['group']));
    }
  }

  /**
   * @return array
   */
  public function getGroupInfo() {
    return $this->groupInfo;
  }

  /**
   * @param array $groupInfo
   */
  public function setGroupInfo($groupInfo) {
    $this->groupInfo = $groupInfo;
  }


  /** {{@inheritdoc}} */
  protected function setKeyBuild($key, $build) {
    $build = parent::setKeyBuild($key, $build);

    return $build;
  }

  /**
   * Builds the value for a given key.
   *
   * @param string $key
   *   The key to build.
   *
   * @return mixed
   */
  protected function buildKey($key) {
    if (!empty($this->structure[$key]['method'])) {
      $method = $this->structure[$key]['method'];
      $build  = $this->$method();
      if (($this->getStructure($key)['type'] == 'array')) {
        if (!empty($this->rawData[$key])) {
          return $this->setKeyBuild($key, array_replace_recursive($build, $this->rawData[$key]));
        }
        else {
          return $this->setKeyBuild($key, $build);
        }
      }
      else {
        return $this->setKeyBuild($key, $build);
      }

    }
    else {
      if (isset($this->structure[$key]['default'])) {
        return $this->buildKeyDefault($key);
      }
    }
  }

  /**
   * Builds the root path.
   *
   * @return string
   */
  protected function buildRootPath() {
    if (($group = $this->getBuild('group')) && isset($group)) {
      return $this->processValueTemplate('%toolbox_info_module_path%/%toolbox_info_labels_machine_name_plural%');
    }
    else {
      return $this->processValueTemplate('admin/structure/%toolbox_info_labels_machine_name_plural%');
    }
  }

  /**
   * Builds the labels.
   *
   * @return array
   */
  protected function buildLabels() {
    $build = $this->getKeyBuilder('labels')->build();

    return $build;
  }

  protected function buildHasRevisions() {
  }

  protected function buildHasTranslations() {
  }

  protected function buildExportable() {
  }

  /**
   * Builds the classes.
   *
   * @return array
   */
  protected function buildClasses() {
    return $this->getKeyBuilder('classes')->build();
  }

  /**
   * Builds the properties.
   *
   * @return array
   */
  protected function buildProperties() {
    return $this->getKeyBuilder('properties')->build();
  }

  /**
   * Builds the tables.
   *
   * @return string
   */
  protected function buildTables() {
    $tables = $this->getKeyBuilder('tables')->build();
    if (!$this->getBuild('has_revisions')) {
      $tables['revision'] = NULL;
      if (!empty($tables['relation_revision'])) {
        $tables['relation_revision'] = array();
      }
    }

    return $tables;
  }

  /**
   * Builds the callbacks.
   *
   * @return array
   */
  protected function buildCallbacks() {
    return $this->getKeyBuilder('callbacks')->build();
  }

  /**
   * Builds the operations.
   *
   * @return array
   */
  protected function buildOperations() {
    return $this->getKeyBuilder('operations')->build();
  }

  /**
   * Builds the keys.
   *
   * @return array
   */
  protected function buildKeys() {
    $keys = array();
    foreach ($this->getBuild('properties') as $property => $info) {
      if ($info['key']) {
        $keys[$info['key']] = $property;
      }
    }

    return $keys;
  }

  /**
   * Builds the children_inherit.
   *
   * @return array
   */
  protected function buildChildrenInherit() {
    $inherit = array();
    foreach ($this->getBuild('properties') as $property => $info) {
      if ($info['children_inherit'] === TRUE) {
        $inherit[] = $property;
      }
    }

    return $inherit;
  }

  /**
   * Builds the group.
   *
   * @return string
   */
  protected function buildGroup() {
  }
}